# FE8 apworld Setup

(This document is adapted from the equivalent for [Pokemon Emerald](https://gist.github.com/Zunawe/406ea7a7ff50db9bf80e4bd040009fed))

Welcome! Feel free to ask for help in the [Discord channel](https://discord.com/channels/731205301247803413/1098762105445953546) if you get stuck at any point. There are a lot of steps for a first time setup, especially if you're new to Archipelago, but we don't want it to overwhelm you. There are many nice people who know the answers to your questions and are willing to help.

## Changes to setup in 0.2.0

In release 0.2.0, FE8 has transitioned to using the generic Bizhawk client. If you need instructions for a prior version, check [this version](https://github.com/CT075/fe8-archipelago/blob/9fec147178b3e0b628fb8b866b082dfcfd93a9e3/setup.md) of the guide.

If you have previously set up the FE8 connector and are familiar with this process, here is a quickstart:

- Include `_bizhawk.apworld` alongside `fe8.apworld`. This won't be necessary once Archipelago version 0.4.4 releases.
- Open the Bizhawk client instead of the FE8 client. As a player, it will be pretty much the same.
- The Bizhawk client will install a new connector script named `connector_bizhawk_generic.lua`. The old `connector_fe8.lua` won't work, delete it.

## Requirements

- An English copy of Fire Emblem: The Sacred Stones. The Archipelago community cannot provide this.
- FE8 apworld: [Latest Release](https://github.com/CT075/Archipelago/releases/latest)
- Bizhawk client Beta 2: [Release](https://github.com/Zunawe/Archipelago/releases/tag/bizhawk_beta-2)
- Archipelago (need 0.4.2 or newer): [Latest Release](https://github.com/ArchipelagoMW/Archipelago/releases/latest)
- BizHawk (need 2.7 or newer): [Downloads Page](https://tasvideos.org/BizHawk/ReleaseHistory)

## Installation

1. Install Archipelago first. During installation, uncheck any games you don't intend to play. Don't worry, you can add them later by running the installer again.
2. Find where Archipelago was installed. On Windows, the default installation directory is `C:\ProgramData\Archipelago`.
3. Place the `fe8.apworld` file into `Archipelago/lib/custom_worlds/`.
4. To verify the apworld is installed correctly, run `ArchipelagoLauncher.exe`. You should find "Bizhawk Client" in the list on the right side.

## Creating a Settings File (YAML)

With the Archipelago launcher open,
1. Click "Generate Template Settings" to create a template for all games and installed apworlds.
2. Copy `Fire Emblem Sacred Stones.yaml` from that directory and modify it to your liking.

If you're interested in randomizing your _settings_, you'll find instructions at the top of the file explaining how to read and edit the weighted settings. But it's likely you just want to set most or all of them to a specific value. In that case you can just set the option directly like you see in settings generated on the website. For example, these two snippets achieve the same result:

```yaml
  easier_5x:
    false: 0
    true: 50
```

```yaml
  easier_5x: true
```

The same goes for numeric options, even if they look slightly more confusing at first. These do the same thing:

```yaml
  min_endgame_level_cap:
    40: 50
    random: 0
    random-low: 0
    random-high: 0
```

```yaml
  min_endgame_level_cap: 40
```

## Generating

If a game includes FE8, you must generate it locally (not on the website). The computer generating the multiworld _and_ the players playing FE8 will both need to install the apworld and have a copy of the vanilla ROM. There are general instructions for generating games [this section of the general setup tutorial](https://archipelago.gg/tutorial/Archipelago/setup/en#generating-a-multiplayer-game).

## Hosting

Once you've generated a game, it _can_ be hosted on the main site. But keep in mind that the patch files will _not_ have download links on the room page. They'll be in the output zip and must be distributed manually. To host on the site, you just have to upload the output zip [here](https://archipelago.gg/uploads) and create a room. Again, there are detailed instructions for hosting [in the general setup tutorial](https://archipelago.gg/tutorial/Archipelago/setup/en#hosting-an-archipelago-server).

## Patching

Now that you have your patch file (which should have the `.apfe8` file extension),

1. Drag that patch file onto `ArchipelagoLauncher.exe` in your file explorer.
2. You may be asked to navigate to your vanilla FE8 ROM.
3. This will automatically create a new patched `.gba` ROM in the same directory as the patch file.
4. BizHawk Client will open when the patching is done, and the program will attempt to open the patched ROM in whatever emulator you've associated `.gba` files with.

If you're playing a single-player seed and you don't care about autotracking or hints, you can stop here, close the client, and load the patched ROM in any emulator. However, for multiworlds and other Archipelago features, continue below using BizHawk as your emulator.

## Configuring BizHawk

You'll only have to do this once. If you've configured BizHawk for other Archipelago games, you're probably all set. Once you have installed BizHawk, open `EmuHawk.exe` and change the following settings:

- If you're using BizHawk 2.7 or 2.8, go to `Config > Customize`. On the Advanced tab, switch the Lua Core from `NLua+KopiLua` to `Lua+LuaInterface`, then restart EmuHawk. (If you're using BizHawk 2.9, you can skip this step.)
- Under `Config > Customize`, enable the "Run in background" option to prevent disconnecting from the client while you're tabbed out of EmuHawk.
- Open a `.gba` file in EmuHawk and go to `Config > Controllers…` to configure your inputs. If you can't click `Controllers… `, load any `.gba` ROM.
- Consider clearing keybinds in `Config > Hotkeys…` if you don't plan to use them. Select the keybind and press Esc to clear it.

## Connecting

1. If the Bizhawk Client isn't running, you can open it either by opening the Archipelago launcher and selecting "Bizhawk Client" in the right column, or by dragging the patch file onto `ArchipelagoLauncher.exe` again.
2. Ensure EmuHawk is running the patched ROM.
3. In EmuHawk, go to `Tools > Lua Console`. This window must stay open while playing.
4. In the Lua Console window, go to `Script > Open Script…`.
5. Navigate to your Archipelago install folder and open `data/lua/connector_bizhawk_generic.lua`. The Lua Console should indicate that it connected to the client.  
If the emulator is freezing every few seconds, that's expected; it's just searching for the client. It will resolve once the client is open and connected.    
If you're feeling adventurous in the future, you can drag the lua script directly onto the emulator screen to open it instead of manually opening the Lua Console window and finding the file.
6. To connect the client to the server, enter your room's `<address>:<port>` into the top text field of the client and click `Connect`.

You're good to go. You should now be able to receive and send items. You'll need to follow these steps every time you want to reconnect. If your connection ever drops, don't worry; just save your game, close both the client and emulator, and repeat these steps. Any items that you missed will be received, and any locations you checked will be sent as soon as you reconnect, even if you made progress offline. Disconnects can occur if emulation is paused for more than a few seconds (e.g. spending time in a menu or resizing the window).

