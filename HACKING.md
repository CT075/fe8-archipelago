This document is intended for potential contributors and future maintainers.

# Building this project

## Requirements

### Build tools

The primary build driver of this project is [ColorzCore](https://github.com/FireEmblemUniverse/ColorzCore), which is vendored [here](bin/ColorzCore).

You will need the [latest .NET SDK](https://docs.microsoft.com/en-us/dotnet/core/install/linux) to build ColorzCore.

To build the various auxiliary scripts, you will need:

- `cmake`
- Haskell GHC >= 9.6.2 and cabal >= 3.6.2.0
- Python >= 3.9

On Debian/Ubuntu/Mint, you can install these via:

```bash
sudo apt install \
  cmake ghc cabal-install
```

### Building the project

To complete the build, you will also need

- [devkitARM](https://devkitpro.org/wiki/devkitARM)
- [bsdiff4](https://github.com/ilanschnell/bsdiff4)
- A clean FE8 (U) ROM (md5: `005531fef9efbb642095fb8f64645236`) named `fe8.gba`
  at the root of the project

## Setup

Run `make` at the project root. This should create `fe8_ap.gba`, along with
`fe8_ap_base.bsdiff4` and a few other intermediate files.

## Copying to Archipelago

At the moment, many of the Archipelago files rely on hardcoded IDs and offsets
that are only known at the build-time of this project. To automatically copy
`fe8_ap_base.bsdiff4` and populate the relevant files, run
`make install_to_archipelago` with the environment variable `ARCHIPELAGO_LOC`
set to a local fork of the main Archipelago repo.

# Project structure

This project uses [Event Assembler](https://feuniverse.us/t/event-assembler/1749)
(specifically, [ColorzCore](https://github.com/FireEmblemUniverse/ColorzCore))
in concert with make as its main build driver. The precise mechanics of how an
EA buildfile works are out of scope for this document --
[this](https://feuniverse.us/t/contros-buildfile-tutorial/14088/2) post on
FEU gives a pretty good layman's rundown of the syntax, but it should be
reasonably self-explanatory to anyone familiar with systems-level C.

The key entry point to the build is the main buildfile [here](main.event).

## Address and index syncing

To ensure that the basepatch and APworld indices never drift out of sync, all
relevant definitions are generated from a common source at build time and are
marked as `connector_config` files. This generation logic lives
[here](bin/connector_config/Generate.hs) and generates C, Event and Python
files that are used. Any kind of magic number or id generation is done through
this generator.

RAM/ROM addresses that the client must be aware of (to handle incoming/outgoing
items and to toggle config items) must be populated *after* the build. For this
purpose, `connector_config.py` is generated with placeholders, then
[post-processed](bin/postprocess.py) to fill it with symbols from the final
symbol table.

## RAM and save allocation

To avoid needing to manually address-munge, [RAM](data/ram_structures.csv) and
[savedata](data/save_structures.csv) allocations are done declaratively and
used to generate the relevant files ([RAM allocator](bin/ram_alloc.py),
[savedata allocator](bin/save_alloc.py)).

(TODO: document how these work better)

## Miscellaneous technical details

### `lyn` autohooks

If you haven't encountered an EA buildfile before, the actual process by which
functions are overwritten may seem a bit mysterious.

[lyn](https://feuniverse.us/t/ea-asm-tool-lyn-elf2ea-if-you-will/2986) is a
tool that converts C object files to Event Assembler code. The tool searches
for functions matching the name of a function in FE8's decompilation (see
[`fe8-symbols.s`](vendor/fe8-symbols.s), and upon finding one, will
automatically insert a jump from the vanilla function of that name to our new
code.

This can cause problems when replacing extremely small functions, as the hook
may be larger than the function being replaced. In such cases, we have no
choice but to override that function manually.

### Build process definitions

The makefiles in this project are designed to be "modular" in that they do not
need to know where in the directory structure they live. To do this, we use
the technique outlined in [this blog post](http://sites.e-advies.nl/nonrecursive-make.html).
Ideally, we would generate dependencies from both C source files and event
files, but I'm dissatisfied with existing techniques to do this. Because of
limitations with gcc's dependency generation, it may be necessary to
periodically delete `_build/cache` if certain changes aren't being picked up.

Most of the big-picture logic is defined in [Rules.mk](Rules.mk), with
module-specific functionality delegated to those sub-makefiles.

### CR comments

You may see comments in the code marked as `CR`, `CR-soon` or `CR-someday`.
This is a habit I picked up from an old workplace of mine, and they are
effectively slightly more greppable `TODO`s of varying level of urgency --

- `CR` is the most important; fix ASAP
- `CR-soon` is a sign of some impending tech debt, but not yet an active problem.
- `CR-someday` is an [Ozymandias](http://thecodelesscode.com/case/234) comment.

Contributors shouldn't feel the need to follow my convention here (I'm probably
not even that consistent with it myself).

### Code style and formatting

- Prefer C to assembly, except for extremely minor edits.
- Use the decomp headers over the GBAFE-CLib headers (the latter is only
  vendored in to allow building against some vendored dependencies,
  particularly Expanded Modular Save). Don't `#include gbafe.h` even though
  such a file exists in the decomp headers, because it conflicts with the same
  file in CLib.
- Two-space soft tabs and `camelCase` names (with the first letter lowercased).
  It's a bit unfortunate that this conflicts with the standard used by the
  decomp (which uses `FirstLetterCaps` instead), but this has a stealth benefit
  of immediately marking which functions are overriding some vanilla
  functionality.
- `type *pointer` over `type* pointer`.
- Avoid using `#incext` and `#inctext` wherever possible. These should pretty
  much always be replaced by invoking the relevant tool in the makefile.

# Current "major" buglist (unordered)

1. Alt route autoleveling
  - This is related to the general exp display bug. The game uses the in-game
    autolevel function to make specific characters stronger at join-time in
    routes when they arrive later. This function checks the same level cap
    function that we hijack for archipelago, meaning that they can be given
    "overcap" exp without leveling if it would put them over the level cap.
    This most commonly occurs with Duessel on Eirika's route.
  - The easiest thing to do is probably to have an alt autolevel function that
    doesn't check the level cap.
  - Medium priority
2. Rescuedropping on invalid terrain bug
  - This actually affects more than rescue-dropping -- both Warp and Rescue (the
    staff) can also cause units to be placed on invalid terrain. The root cause
    is that `moveCostFix` uses movement cost 31 as a sentinel value for "allow
    unit to walk here, but only if stuck". The routines that force-place a unit
    only check for 255 as invalid, so such terrain types are considered valid.
    The easy fix is honestly just to amend these functions to also check for 31.
  - Low priority; the player has to go out of their way to use this. It does
    enable cheesing some chapters (most notably 5x, but also Jehanna Hall), but
    I'm willing to accept that for now.
3. Summoning
  - The summon menu has specific entries for Ewan, Knoll and Lyon, with other
    characters not being allowed to summon. I suppose the easiest thing to do
    here would be to randomly assign every unit in the game one of these, but
    that would either require a ton of data entry/repointing, or we'd have to
    adjust the summoning logic to allow this.
  - Low priority (good starter issue!)
