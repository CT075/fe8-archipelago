# CR cam: We should move to just using fe8_ap.sym directly.

import csv
import enum
import hashlib
import json

DIGEST_LENGTH = len("FIREEMBLEM2EBE8E") - len("FE8AP")
ROM_NAME_BASE = 0xA0
HEADER_CHECKSUM_OFFS = 0xBD


class SymbolTable:
    symbols: dict[str, int]
    seen: dict[str, int]

    def __init__(self, symbols: dict[str, int]):
        self.symbols = symbols
        self.seen = dict()

    def __getitem__(self, k: str) -> int:
        result = self.symbols[k]
        self.seen[k] = result
        return result

    # We mint a new client version when a symbol exported to an Archipelago
    # install changes its location. This is technically too sensitive (renames
    # will force a spurious version bump), but using the names in the digest
    # is the easiest way to catch reordering.
    def exported_symbols_digest(self) -> str:
        version_hash = hashlib.md5(json.dumps(self.seen, sort_keys=True).encode())
        return version_hash.hexdigest()[:DIGEST_LENGTH].upper()


def process_symbol(s: str, symbols: SymbolTable) -> str:
    if ":" not in s:
        return f"0x{symbols[s]:X}"

    prefix, rest = s.split(":")

    match prefix:
        case "ROM_BASE":
            v = symbols[rest]
            return f"0x{v-0x08000000:X}"

    raise ValueError(f"unknown symbol display modifier {prefix}")


def populate_text(s: str, symbols: SymbolTable) -> str:
    class ParserState(enum.Enum):
        NEUTRAL = "neutral"
        SEEN_BRACE = "seen"
        SYMBOL = "sym"
        END_SYMBOL = "endsym"

    state = ParserState.NEUTRAL
    current_symbol = ""
    result = ""

    for c in s:
        match state:
            case ParserState.NEUTRAL:
                if c == "{":
                    state = ParserState.SEEN_BRACE
                else:
                    result += c
            case ParserState.SEEN_BRACE:
                if c == "|":
                    state = ParserState.SYMBOL
                else:
                    result += "{" + f"{c}"
                    state = ParserState.NEUTRAL
            case ParserState.SYMBOL:
                if c == "|":
                    state = ParserState.END_SYMBOL
                else:
                    current_symbol += c
            case ParserState.END_SYMBOL:
                if c == "}":
                    state = ParserState.NEUTRAL
                    result += str(process_symbol(current_symbol, symbols))
                    current_symbol = ""
                else:
                    result += "{|" + f"{current_symbol}" + "|"
                    state = ParserState.NEUTRAL

    return result


def main(sym_file: str, inp: str, out: str, target: str):
    with open(sym_file) as f:
        reader = csv.reader(f, delimiter=" ")
        symbols = {sym: int(addr, 16) for addr, sym in reader}

    with open(inp) as f:
        connector_config = f.read()

    symbol_table = SymbolTable(symbols)

    populated_template = populate_text(connector_config, symbol_table)
    rom_name = f"FE8AP{symbol_table.exported_symbols_digest()}"

    with open(out, "w") as f:
        f.write(populated_template)
        f.write("\n")
        f.write(f'EXPECTED_ROM_NAME = "{rom_name}"')

    with open(target, "rb") as f:
        romdata = bytearray(f.read())
        assert len(rom_name) == len("FIREEMBLEM2EBE8E")
        check = 0
        for i, c in enumerate(rom_name.encode("utf-8")):
            romdata[ROM_NAME_BASE + i] = c
            check -= c

        for c in b"01\x96":
            check -= c

        check -= 0x19
        check %= 256

        romdata[HEADER_CHECKSUM_OFFS] = check

    with open(target, "wb") as f:
        f.write(romdata)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        prog="PopulateSymbols", description="Populate templates with no$ symbols"
    )

    parser.add_argument("-f", "--sym_file")
    parser.add_argument("--connector_config_in")
    parser.add_argument("--connector_config_out")
    parser.add_argument("--target")

    args = parser.parse_args()

    main(
        sym_file=args.sym_file,
        inp=args.connector_config_in,
        out=args.connector_config_out,
        target=args.target,
    )
