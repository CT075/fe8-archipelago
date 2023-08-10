#!/usr/bin/env python

import sys
import argparse
from pathlib import PurePath, Path

chunks = [
    ("ch10eirEndScene", 0x9F43F8, 0x9F4630),
    ("ch10ephEndScene", 0x9FAC20, 0x9FAED8),
    ("ch11eirEndScene", 0x9F4A7C, 0x9F4E50),
    ("ch11ephEndScene", 0x9FB318, 0x9FB390),
    ("ch12eirEndScene", 0x9F51B0, 0x9F5368),
    ("ch12ephEndScene", 0x9FB770, 0x9FB908),
    ("ch13eirEndScene", 0x9F5798, 0x9F59C8),
    ("ch13ephEndScene", 0x9FBC0C, 0x9FBC88),
    ("ch14eirEndScene", 0x9F5DB8, 0x9F6198),
    ("ch14ephEndScene", 0x9FC06C, 0x9FC51C),
    ("ch15eirEndScene", 0x9F6470, 0x9F6480),
    ("ch15ephEndScene", 0x9FC8F0, 0x9FC900),
    ("ch16eirEndScene", 0x9F6E40, 0x9F6E4C),
    ("ch16ephEndScene", 0x9FCD98, 0x9FCDA4),
    ("ch17eirEndScene", 0x9F79C4, 0x9F79D0),
    ("ch17ephEndScene", 0x9FCEDC, 0x9FCEE8),
    ("ch18eirEndScene", 0x9F7F88, 0x9F81B8),
    ("ch18ephEndScene", 0x9FD068, 0x9FD264),
    ("ch19eirEndScene", 0x9F8678, 0x9F8684),
    ("ch19ephEndScene", 0x9FD3DC, 0x9FD3E8),
    ("ch1EndScene", 0x9EFAC4, 0x9EFB34),
    ("ch20eirEndScene", 0x9F8C8C, 0x9F8CC8),
    ("ch20ephEndScene", 0x9FD584, 0x9FD62C),
    ("ch2EndScene", 0x9F04B4, 0x9F05F8),
    ("ch3EndScene", 0x9F13CC, 0x9F1564),
    ("ch4EndScene", 0x9F19F8, 0x9F1B34),
    ("ch5EndScene", 0x9F2090, 0x9F216C),
    ("ch5xEndScene", 0x9F25FC, 0x9F2714),
    ("ch6EndScene", 0x9F29FC, 0x9F2A94),
    ("ch7EndScene", 0x9F2D28, 0x9F2E68),
    ("ch8EndScene", 0x9F318C, 0x9F31B4),
    ("ch9eirEndScene", 0x9F3DB8, 0x9F3F48),
    ("ch9ephEndScene", 0x9FA4E0, 0x9FA630),
    ("final1eirEndScene", 0x9F92A0, 0x9F9310),
    ("final1ephEndScene", 0x9FD9B8, 0x9FDA28),
    ("final2eirEndScene", 0x9F9F10, 0x9F9F1C),
    ("final2ephEndScene", 0x9FDB58, 0x9FDB64),
    ("prologueEndScene", 0x9EF164, 0x9EF1B8),
]


def extract_chunks(rom: Path, dir: Path):
    with open(rom, "rb") as f:
        bs = f.read()
    for chunk_name, chunk_start, chunk_end in chunks:
        with open(dir / f"{chunk_name}.dmp", "wb") as f:
            f.write(bs[chunk_start:chunk_end])


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="rip blobs from baserom")
    parser.add_argument("baserom", type=Path, help="path to baserom")
    parser.add_argument("output_dir", type=Path, help="output data folder")
    p = parser.parse_args()
    extract_chunks(p.baserom, p.output_dir)
