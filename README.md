# MiSTer × Stream Deck
### Animated console launchers. A shortcut page at your fingertips.

[![Build and release](https://github.com/pxpxpxp/MiSTer_StreamDeck/actions/workflows/release.yml/badge.svg)](https://github.com/pxpxpxp/MiSTer_StreamDeck/actions/workflows/release.yml)
![Version](https://img.shields.io/badge/release-v1-74e5c7)
![Device](https://img.shields.io/badge/Stream_Deck-MK.2_%C2%B7_15_keys-253a55)

Turn an **Elgato Stream Deck MK.2** into a native MiSTer launcher with animated character artwork, console shortcuts, background updates, and five ascending brightness levels. Hold one button to reveal a second page for menu navigation and controller mapping.

**[Download v1 ZIP](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/download/v1/MiSTer_StreamDeck_v1.zip)** · **[Read the animated guide](https://pxpxpxp.github.io/MiSTer_StreamDeck/)** · **[Open the Deck Editor](https://pxpxpxp.github.io/MiSTer_StreamDeck/editor/)**

## Six-key Stream Deck Mini

The Mini now has a separate [Mini build and instructions](mini/README.md) and [animated Mini guide](https://pxpxpxp.github.io/MiSTer_StreamDeck/mini.html). **Update All is on its first page, key 4.** [Download Mini v1.0.0](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/download/mini-v1.0.0/MiSTer_StreamDeck_Mini_v1_0_0.zip). The 15-key MK.2 package and editor below remain separate.

## What you get

- **Animated console buttons** with character artwork and a colorful startup mosaic that fades in and out.
- **Two pages:** launch your games on page one; navigate MiSTer and map controllers on page two.
- **Matching green press feedback:** each shortcut keeps its own artwork while held.
- **Animated shortcuts:** distinct small movements, clean pixel edges, equal-width Menu bars, and Back morphing into Stay Puft every fifth cycle.
- **Update All feedback:** a running spinner, a green completion pulse, then the gray finished state.
- **Five ascending brightness levels** on a single button.
- **An offline editor** for button actions, paths, artwork, and both page layouts.

## Install

1. **Download and extract** [MiSTer_StreamDeck_v1.zip](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/download/v1/MiSTer_StreamDeck_v1.zip).
2. If upgrading, wait for any Update All job to finish, then run **StreamDeck_Disable.sh**. Back up your customized configurations or saved editor project.
3. Copy the ZIP’s **Scripts contents** into `/media/fat/Scripts/`, including the hidden **.config** folder. Copy the binary, configurations, and artwork together.
4. Connect the deck to MiSTer’s **USB host hub** with a USB-A–to–USB-C **data cable**.
5. Run **StreamDeck_Enable.sh** from MiSTer’s Scripts menu.

The launcher installs directly in `/media/fat/Scripts/.config/streamdeck/`. Keep **Deck_Editor** on your computer.

> **Show hidden files when copying:** in macOS Finder, press **Command–Shift–period**; in Windows Explorer, enable **View → Show → Hidden items**.

Install the cores, BIOS files, games, and `Scripts/update_all.sh` separately.

## Page one · Launch and control

Physical buttons are numbered **1–15**, left to right across each row.

| 1 · NES | 2 · SNES | 3 · Genesis | 4 · TurboGrafx-16 | 5 · PlayStation |
| :---: | :---: | :---: | :---: | :---: |
| **6 · Saturn** | **7 · Nintendo 64** | **8 · Mega CD** | **9 · Game Boy Advance** | **10 · Game Boy** |
| **11 · Master System** | **12 · Neo Geo** | **13 · The Simpsons** | **14 · Update All** | **15 · Brightness / Page two** |

**Button 15 — Stay Puft:** tap to cycle brightness upward; hold for **one second** to open the shortcut page. Release before using the newly opened page.

SNES defaults to the **Donkey Kong Country (USA) (Rev 2)** favorite launcher. Genesis uses the **MegaDrive** core. Check your installed paths in the editor, especially the Donkey Kong Country favorite and Simpsons arcade launcher.

## Page two · Navigate and map

| 1 · Menu / F12 | 2 · — | 3 · ↑ Up | 4 · — | 5 · Escape |
| :---: | :---: | :---: | :---: | :---: |
| **6 · —** | **7 · ← Left** | **8 · ↓ Down** | **9 · → Right** | **10 · Enter** |
| **11 · Space** | **12 · —** | **13 · —** | **14 · —** | **15 · Back** |

Each active shortcut animates and turns **green while held**, then returns to its normal color on release. Back morphs into **Stay Puft every fifth animation cycle**. Press and release **Back** to return to page one.

| Shortcut | Use |
| --- | --- |
| **Menu / F12** | Open or close MiSTer’s menu |
| **Arrows** | Navigate menu items |
| **Enter** | Select an item or finish controller mapping |
| **Space** | Skip a controller-mapping entry |
| **Escape** | Back out or cancel mapping |
| **Back** | Return to the console page |

For controller mapping, use the Stream Deck to open the mapping menu, then answer MiSTer’s prompts with your controller. Use Space, Enter, and Escape as needed.

## Customize your deck

Open the [Deck Editor](https://pxpxpxp.github.io/MiSTer_StreamDeck/editor/) or the downloaded `Deck_Editor/index.html` on your computer.

1. Select **Consoles** or **Shortcuts**.
2. Choose a button and edit its action, target, label, or artwork.
3. **Save project** to retain an editable copy.
4. **Export for MiSTer**, disable the installed launcher, copy the exported configuration and artwork, then enable it again.

Labels are metadata; visible lettering is part of the artwork. Imported GIFs must be exported as prepared animations for MiSTer.

## Build and verification

[GitHub Actions](https://github.com/pxpxpxp/MiSTer_StreamDeck/actions/workflows/release.yml) restores the v1 build inputs, applies the current shortcut layout and feedback changes, runs host checks, and builds a **static Cortex-A9 ARM binary** with **Zig 0.13.0**. It publishes the installable ZIP and its SHA-256 checksum.

The repository stores the original build inputs in `build-inputs/` as text-encoded archive parts, with an integrity check in the workflow. The current layout, animation, and feedback changes are in `tools/`. The release includes the resulting C source and tests under `Scripts/.config/streamdeck/source/`.

The build checks include configuration and failure handling, page switching, held-button feedback, prepared-animation loading, and memory behavior. The latest published build passed these checks. Hardware timing and USB behavior should also be checked on your MiSTer.

To build the extracted source on a computer with Zig installed:

```sh
cd Scripts/.config/streamdeck
sh source/build.sh
```

Runtime artwork uses cached JPEG frames; MiSTer does not decode GIFs during playback.

## Troubleshooting

- **Wrong or stale button artwork:** copy the matching binary, both configurations, and the full icons folder; run Disable followed by Enable.
- **Shortcut keys do nothing:** check the USB connection and the launcher diagnostics for a virtual-keyboard error.
- **A game does not launch:** confirm the exact installed core, favorite `.mgl`, or arcade `.mra` path.
- **Update All fails:** confirm Bash and `/media/fat/Scripts/update_all.sh` are installed; inspect the script log.

The downloaded package includes `extras/StreamDeck_Diagnostics.sh`. See the [guide’s Customize & help page](https://pxpxpxp.github.io/MiSTer_StreamDeck/) for recovery instructions.

## Credits and licensing

The release includes **LICENSE.txt** and **ARTWORK_CREDITS.txt** with licensing and artwork attribution. Characters, console logos, and trademarks belong to their respective owners. Third-party notices are retained in the package.

---

**[Download](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/download/v1/MiSTer_StreamDeck_v1.zip)** · **[Guide](https://pxpxpxp.github.io/MiSTer_StreamDeck/)** · **[Editor](https://pxpxpxp.github.io/MiSTer_StreamDeck/editor/)** · **[Releases](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases)**
