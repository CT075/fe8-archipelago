#!/usr/bin/env python

import sys
import argparse
from pathlib import PurePath, Path

# Talk event (character event) recruitment scripts.
# Each entry: (name, start, end) where addresses are ROM file offsets (no 0x08000000 base).
#
# Units that join via character (talk) events are straightforward: we hook the event
# script that runs when the recruitment conversation happens.
#
# For units with multiple recruiters (e.g. Eirika OR Seth can recruit Franz), each
# recruiter script fires markFranzRecruited. handleLocationGet is idempotent so
# double-firing is safe; the flag on the character event table ensures only one fires.

talk_chunks = [
    # Ch1 - Franz (Seth talks to him, OR Eirika talks to him)
    ("ch1TalkSethFranz",     0x9EFB38, 0x9EFB38 + 0x20),
    ("ch1TalkEirikaFranz",   0x9EFB58, 0x9EFB58 + 0x20),

    # Ch2 - Ross (Eirika recruits), Garcia (Ross recruits)
    ("ch2TalkEirikaRoss",    0x9F05FC, 0x9F05FC + 0x2C),
    ("ch2TalkRossGarcia",    0x9F0628, 0x9F0628 + 0x28),

    # Ch3 - Colm (Neimi recruits)
    ("ch3TalkNeimiColm",     0x9F1568, 0x9F1568 + 0x38),

    # Ch5 - Joshua (Natasha recruits)
    ("ch5TalkNatashaJoshua", 0x9F2270, 0x9F2270 + 0x34),

    # Ch8 - Kyle (Seth recruits), Forde (Franz recruits)
    ("ch8TalkSethKyle",      0x9F31F4, 0x9F31F4 + 0x20),
    ("ch8TalkFranzForde",    0x9F3214, 0x9F3214 + 0x20),

    # Ch9a (Eirika route) - Amelia (Eirika or Franz recruits)
    ("ch9aEirTalkEirikaAmelia", 0x9F3F4C, 0x9F3F4C + 0x28),
    ("ch9aEirTalkFranzAmelia",  0x9F3F74, 0x9F3F74 + 0x28),

    # Ch10a (Eirika route) - Innes, Gerik, Tethys, Marisa
    ("ch10aEirTalkEirikaInnes",  0x9F4634, 0x9F4634 + 0x28),
    ("ch10aEirTalkTanaInnes",    0x9F465C, 0x9F465C + 0x28),
    ("ch10aEirTalkInnesGerik",   0x9F4684, 0x9F4684 + 0x28),
    ("ch10aEirTalkTethysGerik",  0x9F46AC, 0x9F46AC + 0x28),
    ("ch10aEirTalkInnesTethys",  0x9F46D4, 0x9F46D4 + 0x28),
    ("ch10aEirTalkGerikTethys",  0x9F46FC, 0x9F46FC + 0x28),
    ("ch10aEirTalkGerikMarisa",  0x9F4724, 0x9F4724 + 0x2C),

    # Ch11a (Eirika route) - L'Arachel (Eirika recruits), Dozla (L'Arachel recruits)
    ("ch11aEirTalkEirikaLArachel", 0x9F4E54, 0x9F4E54 + 0x28),
    ("ch11aEirTalkLArachelDozla",  0x9F4E7C, 0x9F4E7C + 0x28),

    # Ch13a (Eirika route) - Amelia alt (missed Ch9a), Cormag
    ("ch13aEirTalkEirikaAmelia", 0x9F59CC, 0x9F59CC + 0x2C),
    ("ch13aEirTalkFranzAmelia",  0x9F59F8, 0x9F59F8 + 0x28),
    ("ch13aEirTalkEirikaCormag", 0x9F5A20, 0x9F5A20 + 0x28),

    # Ch14a (Eirika route) - Rennac (L'Arachel or Eirika recruits)
    ("ch14aEirTalkLArachelRennac", 0x9F619C, 0x9F619C + 0x28),
    ("ch14aEirTalkEirikaRennac",   0x9F61C4, 0x9F61C4 + 0x74),

    # Ch17a (Eirika route) - Syrene (Innes, Tana, or Vanessa recruits)
    ("ch17aEirTalkInnesSyrene",   0x9F7CAC, 0x9F7CAC + 0x28),
    ("ch17aEirTalkTanaSyrene",    0x9F7CD4, 0x9F7CD4 + 0x28),
    ("ch17aEirTalkVanessaSyrene", 0x9F7CFC, 0x9F7CFC + 0x28),

    # Ch9b (Ephraim route) - Amelia (Ephraim or Franz recruits), Tana (Ephraim recruits)
    ("ch9bEphTalkEphAmelia",   0x9FA634, 0x9FA634 + 0x28),
    ("ch9bEphTalkFranzAmelia", 0x9FA65C, 0x9FA65C + 0x34),
    ("ch9bEphTalkEphTana",     0x9FA690, 0x9FA690 + 0x24),

    # Ch10b (Ephraim route) - Duessel, Cormag
    ("ch10bEphTalkEphDuessel",    0x9FAEDC, 0x9FAEDC + 0x28),
    ("ch10bEphTalkDuesselCormag", 0x9FAF04, 0x9FAF04 + 0x28),
    ("ch10bEphTalkTanaCormag",    0x9FAF2C, 0x9FAF2C + 0x28),

    # Ch11b (Ephraim route) - L'Arachel, Dozla
    ("ch11bEphTalkEphLArachel",    0x9FB394, 0x9FB394 + 0x28),
    ("ch11bEphTalkLArachelDozla",  0x9FB3BC, 0x9FB3BC + 0x28),

    # Ch12b (Ephraim route) - Marisa (Ewan recruits)
    ("ch12bEphTalkEwanMarisa", 0x9FB90C, 0x9FB90C + 0x28),

    # Ch13b (Ephraim route) - Gerik (Ephraim recruits), Marisa alt, Ewan (Tethys recruits)
    ("ch13bEphTalkEphGerik",    0x9FBD2C, 0x9FBD2C + 0x24),
    ("ch13bEphTalkGerikMarisa", 0x9FBD50, 0x9FBD50 + 0x20),
    ("ch13bEphTalkTethysEwan",  0x9FBD70, 0x9FBD70 + 0x20),

    # Ch14b (Ephraim route) - Rennac (L'Arachel or Ephraim recruits)
    ("ch14bEphTalkLArachelRennac", 0x9FC520, 0x9FC520 + 0x0C),
    ("ch14bEphTalkEphRennac",      0x9FC52C, 0x9FC52C + 0x74),

    # Ch17b (Ephraim route) - Syrene (Innes, Tana, or Vanessa recruits)
    ("ch17bEphTalkInnesSyrene",   0x9FCEEC, 0x9FCEEC + 0x0C),
    ("ch17bEphTalkTanaSyrene",    0x9FCEF8, 0x9FCEF8 + 0x0C),
    ("ch17bEphTalkVanessaSyrene", 0x9FCF04, 0x9FCF04 + 0x0C),
]

# Beginning scene (auto-join) hooks.
# Units in these chapters join automatically at chapter start (no talk event).
beginning_chunks = [
    # Prologue - Seth (already in roster from game start)
    ("prologueBeginScene", 0x9EEBE8, 0x9EEBE8 + 0x0D4),

    # Ch2 - Gilliam, Vanessa, Moulder
    ("ch2BeginScene", 0x9F02A0, 0x9F02A0 + 0x1E4),

    # Ch3 - Neimi, Artur
    ("ch3BeginScene", 0x9F1200, 0x9F1200 + 0x14C),

    # Ch4 - Lute
    ("ch4BeginScene", 0x9F17A4, 0x9F17A4 + 0x1F8),

    # Ch8 - Tana (Eirika route: freed from prison during Ch8 story)
    # TODO: verify - may need to move to ch8EndScene if she joins at chapter end
    ("ch8BeginScene", 0x9F2F38, 0x9F2F38 + 0x1EC),

    # Ch12b (Ephraim route) - Innes, Gerik, Tethys as starting allies
    # TODO: verify these units actually join here
    ("ch12bBeginScene", 0x9FB4D4, 0x9FB4D4 + 0x178),

    # Ch11a (Eirika route) beginning scene - Ewan (travels with L'Arachel)
    # TODO: verify - Ewan may join at Ch12a or Ch13a instead
    ("ch11aBeginScene", 0x9F48F8, 0x9F48F8 + 0x0D0),

    # Ch14a (Eirika route) - Saleh
    # TODO: verify
    ("ch14aBeginScene", 0x9F5B3C, 0x9F5B3C + 0x188),

    # Ch15a (Eirika route) - Knoll (freed from dungeon)
    # TODO: verify - may be via a flag event instead
    ("ch15aBeginScene", 0x9F6344, 0x9F6344 + 0x0C0),

    # Ch16b (Ephraim route) - Knoll, Saleh
    # TODO: verify
    ("ch16bBeginScene", 0x9FCD40, 0x9FCD40 + 0x058),

    # Ch16a (Eirika route) - Myrrh
    ("ch16aBeginScene", 0x9F6A34, 0x9F6A34 + 0x058),
]

all_chunks = talk_chunks + beginning_chunks


def extract_chunks(rom: Path, dir: Path):
    with open(rom, "rb") as f:
        bs = f.read()
    for chunk_name, chunk_start, chunk_end in all_chunks:
        with open(dir / f"{chunk_name}.dmp", "wb") as f:
            f.write(bs[chunk_start:chunk_end])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="rip recruit event blobs from baserom")
    parser.add_argument("baserom", type=Path, help="path to baserom")
    parser.add_argument("output_dir", type=Path, help="output data folder")
    p = parser.parse_args()
    extract_chunks(p.baserom, p.output_dir)
