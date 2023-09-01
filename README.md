# FE8 Archipelago Build

The source for an FE8 Archipelago prototype. Currently intended to be used with
[ColorzCore](https://github.com/minishmaker/randomizer/tree/master/Vendor/ColorzCore)
to build the pre-randomized ROM.

## TODO

### Issues

- For units below the progressive level cap, EXP will display normally despite
  being capped. This is display-only; such units are correctly prevented from
  gaining EXP.

### Organizational

- Move `FillAIDangerMap` and `ExpandedModularSave` to `vendor` from `src`
- Move various vendored tools to `vendor` from `bin`
- Use `_build` to store intermediate artifacts (`.o` files, etc) to avoid clutter

# License and Credits

This code is licensed under the MIT License (see [LICENSE](LICENSE)), except
for vendored resources as follows, which are included under their original
licenses:

- [fireemblem8u](https://github.com/FireEmblemUniverse/fireemblem8u)
  decompilation symbols and headers by various contributors
- FillAIDangerMap by [hypergammaspaces](https://hypergammaspaces.tumblr.com/)
- `lyn`, libgbafe and Expanded Modular Save by [stan](https://github.com/StanHash/)
- Project template initially forked from MysticOCE's
  [EasyBuildfile](https://github.com/MysticOCE/EasyBuildfile) taking
  inspiration from [Zane Avernathy's Sacred Stones hack rewrites](https://github.com/ZaneAvernathy/Rewrite)
