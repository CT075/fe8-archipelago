from collections.abc import Iterable
from dataclasses import dataclass
import csv

HEADER = """\
// THIS FILE IS GENERATED
//
// To change this file, see `bin/ram_alloc.py` and `data/ram_structures.csv`.

#ifndef RAM_STRUCTURES_H
#define RAM_STRUCTURES_H

#include "global.h"

#include "constants.h"
#include "archipelago.h"
#include "progressiveCaps.h"

#define sizeof_round(ty) ((sizeof(ty) + sizeof(int)-1) & ~(sizeof(int)-1))
"""

FOOTER = """\

#endif // RAM_STRUCTURES_H
"""


@dataclass
class Item:
    name: str
    real_type: str
    access_type: str
    notes: str

    def address_name(self):
        return "_".join(word.upper() for word in self.name.split()) + "_ADDR"

    def var_name(self):
        return "".join(
            word.lower() if i == 0 else word for i, word in enumerate(self.name.split())
        )

    def var_declaration(self):
        access_type = self.access_type if self.access_type else f'{self.real_type} *'
        return f"#define {self.var_name()} (({access_type})({self.address_name()}))"


def main(items: Iterable[Item]) -> None:
    last_addr = "FREE_RAM_START"
    bump = "0"

    print(HEADER)
    for item in items:
        print(f"#define {item.address_name()} ({last_addr} + {bump})")
        print(item.var_declaration())
        last_addr = f"{item.address_name()}"
        bump = f"sizeof_round({item.real_type})"
    print(FOOTER)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        prog="AllocRAM", description="Bump-allocate RAM structures in C/EA"
    )

    parser.add_argument("--items_file", required=True)

    args = parser.parse_args()

    with open(args.items_file) as f:
        items = csv.DictReader(f)
        main(items=map(lambda x: Item(**x), items))
