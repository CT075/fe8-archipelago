# CR cam: We should move to just using fe8_ap.sym directly.

import csv
import enum


def process_symbol(s: str, symbols: dict[str, int]) -> str:
    if ":" not in s:
        return f"0x{symbols[s]:X}"

    prefix, rest = s.split(":")
    v = symbols[rest]

    match prefix:
        case "ROM_BASE":
            return f"0x{v-0x08000000:X}"

    raise ValueError(f"unknown symbol display modifier {prefix}")


def populate_text(s: str, symbols: dict[str, int]) -> str:
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


def main(sym_file: str, inp: str) -> str:
    with open(sym_file) as f:
        reader = csv.reader(f, delimiter=" ")
        symbols = {sym: int(addr, 16) for addr, sym in reader}

    with open(inp) as f:
        data = f.read()

    return populate_text(data, symbols)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        prog="PopulateSymbols", description="Populate templates with no$ symbols"
    )

    parser.add_argument("-f", "--sym_file")
    parser.add_argument("--input")

    args = parser.parse_args()

    print(main(sym_file=args.sym_file, inp=args.input))
