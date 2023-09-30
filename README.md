# FE8 Archipelago Build

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

## TODO

### Issues

- For units below the progressive level cap, EXP will display normally despite
  being capped. This is display-only; such units are correctly prevented from
  gaining EXP.
- Receiving items on the world map doesn't work yet.

### Polish

- Seth's weapon can change between his fight with Valter and the actual start
  of the Prologue.

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
- `lyn`, libgbafe and Expanded Modular Save by [stan](https://github.com/StanHash/)
- Project template initially forked from MysticOCE's
  [EasyBuildfile](https://github.com/MysticOCE/EasyBuildfile) taking
  inspiration from [Zane Avernathy's Sacred Stones hack rewrites](https://github.com/ZaneAvernathy/Rewrite)
