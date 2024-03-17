# Building this project

## Requirements

- Make, CMake
- Haskell GHC >= 9.6.2
- cabal >= 3.6.2.0
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
