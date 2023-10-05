# Building this project

## Requirements

- Make, CMake
- Haskell GHC >= 9.6.2
- devkitARM
- [ColorzCore](https://github.com/FireEmblemUniverse/ColorzCore)
- A clean FE8 (U) ROM (md5: `005531fef9efbb642095fb8f64645236`) named `fe8.gba`
  at the root of the project

## Setup

The initial run of `make` will prompt you to locate your version of ColorzCore.
Once you do so, it will create the build environment. Running `make` again
should create `fe8_ap.gba` and `fe8_ap_base.bsdiff4`.

## Copying to Archipelago

At the moment, many of the Archipelago files rely on hardcoded IDs and offsets
that are only known at the build-time of this project. To automatically copy
`fe8_ap_base.bsdiff4` and populate the relevant files, run
`make install_to_archipelago` with the environment variable `ARCHIPELAGO_LOC`
set to a local fork of the main Archipelago repo.
