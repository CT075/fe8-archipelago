from collections.abc import Iterable
from dataclasses import dataclass
import csv


def format_header(which: str) -> str:
    return """\
// THIS FILE IS GENERATED
//
// To change this file, see `bin/ram_alloc.py` and `data/ram_structures.csv`.

#ifndef {0}_GEN_EVENT
#define {0}_GEN_EVENT
""".format(
        which
    )


def format_footer(which: str) -> str:
    return """\
#endif // {0}_GEN_EVENT
""".format(
        which
    )


DATA = {
    "save": {"start": "$0DC8", "end": "$1344", "name": "SAVE_CHUNKS"},
    "suspend": {"start": "$1F78", "end": "$2E78", "name": "SUSPEND_CHUNKS"},
}


@dataclass
class Item:
    name: str
    size: str
    which: str
    save_fn_name: str
    load_fn_name: str

    def format_entry(self, which, offs):
        if self.which not in (which, "both"):
            return
        print(
            f"DeclSaveChunk({offs}, {self.size}, {self.save_fn_name}, {self.load_fn_name})"
        )


def main(items: Iterable[Item], which: str):
    print(format_header(DATA[which]['name']))
    offs = DATA[which]["start"]
    for item in items:
        item.format_entry(which, offs)
        offs += f"+{item.size}"
    print(f"ASSERT {DATA[which]['end']}-({offs})")
    print(format_footer(DATA[which]['name']))


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        prog="AllocSaveChunks", description="Bump-allocate save structures in ExModularSave"
    )

    parser.add_argument("--which", required=True)
    parser.add_argument("--items_file", required=True)

    args = parser.parse_args()

    with open(args.items_file) as f:
        items = csv.DictReader(f)
        if args.which not in ("save", "suspend"):
            print("`--which` argument must be `save` or `suspend`")
        else:
            main(items=map(lambda x: Item(**x), items), which=args.which)
