# FE8 Archipelago Basepatch

The source for an FE8 Archipelago prototype. Currently intended to be used with
[ColorzCore](https://github.com/FireEmblemUniverse/ColorzCore)
to build the pre-randomized ROM.

## What are the checks and rewards?

At the moment, checks are rewarded for:

- Clearing a chapter.
- Receiving a Sacred Twin regalia in a cutscene.

The rewards themselves are:

- Progressive level cap (unpromoted level 10 -> promoted level 20, counts by 5s)
- Progressive weapon level
- A Sacred Twin weapon.

To make the Sacred Twin weapons more impactful, there is also an optional
"Super Demon King" mode which buffs the final boss to take less damage from
non-Sacred Twin weapons.

## What else is planned?

Eventually, Chestsanity and general item randomization.

## Is the actual randomizer in this repo?

No. See my branch of the [main Archipelago repo](https://github.com/CT075/Archipelago/tree/fe8/stable).

## How can I build this project?

See [HACKING.md](HACKING.md).

## TODO

### Issues

- For units above the progressive level cap, EXP will display normally despite
  being capped. This is display-only; such units are correctly prevented from
  gaining EXP.
    - Overflow EXP that a unit gains from below the level cap to above it is
      not properly truncated. This may lead to a unit being level 20 with 11
      EXP.
- Receiving items on the world map doesn't work yet.
- Units can be dropped on impassable terrain. This is a bug resulting from a
  fix that allows units to move one tile in any direction if the game judges
  them to be "stuck". This serves two purposes, first to reduce the chance that
  cutscene pathfinding will crash the game, and second to prevent softlocks if
  a mandatory enemy spawns in an inaccessible area (this is most commonly
  encountered with the chapter 2 brigands). There are a few different ideas for
  fixes outlined for this in [HACKING.md](HACKING.md) if anyone is interested,
  but it is a low priority for me at the moment.

### Polish

- Seth's weapon can change between his fight with Valter and the actual start
  of the Prologue.
- There are a few instances of a boss's cutscene class differing from their
  gameplay class.
- Custom unit palettes are planned, but will not be available for a while.

### Organizational

- Move `ExpandedModularSave` to `vendor` from `src`
- Move various vendored tools to `vendor` from `bin`
- Use `_build` to store intermediate artifacts (`.o` files, etc) to avoid clutter

# License and Credits

This code is licensed under the MIT License (see [LICENSE](LICENSE)), except
for vendored resources as follows, which are included under their original
licenses:

- [fireemblem8u](https://github.com/FireEmblemUniverse/fireemblem8u)
  decompilation symbols and headers by various contributors
- BattleStatsWithAnimsOff by Tequila, with assets by Alusq
- DangerZone, LToggle and HpBars by circleseverywhere
- moveCostFix adapted from [SelfRandomizingRom](https://github.com/FireEmblemUniverse/SelfRandomizingRom-fe8) by circleseverywhere
- `lyn`, libgbafe, text-process-classic and Expanded Modular Save by [stan](https://github.com/StanHash/)
- Inline GenerateBestMovementScript by 7743
- ParseFile and Png2Dmp by [CrazyColorz5](https://github.com/Crazycolorz5)
- FE8 Essential Fixes by the [FE8 Skill System](https://github.com/FireEmblemUniverse/SkillSystem_FE8/) team and contributors
- Project template initially forked from MysticOCE's
  [EasyBuildfile](https://github.com/MysticOCE/EasyBuildfile) taking
  inspiration from [Zane Avernathy's Sacred Stones hack rewrites](https://github.com/ZaneAvernathy/Rewrite)

# Acknowledgments

Of course, this project has been far from a one-man effort. Major technical
contributors to the FE8 Archipelago project include:

- [Teraspark](https://github.com/Teraspark/)
- [Darrman](https://feuniverse.us/u/darrman/)
- [Two Who Belong](https://linktr.ee/ttlaitw)

Finally, special thanks to SgtSmilies, MysticOCE and Datagne for helping me
playtest through the earliest and buggiest versions.
