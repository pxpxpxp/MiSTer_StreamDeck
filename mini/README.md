# MiSTer × Stream Deck Mini · v1.0.0

[Download Mini ZIP](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/download/mini-v1.0.0/MiSTer_StreamDeck_Mini_v1_0_0.zip) · [Animated Mini guide](https://pxpxpxp.github.io/MiSTer_StreamDeck/mini.html) · [15-key MK.2 build](../README.md)

A six-key port of the existing native MiSTer launcher. **Update All is on the first page, physical key 4.** The Mini uses its own USB protocol and prepared 80×80 BMP animations. No image decoding happens on MiSTer.

## Home · Page 1

| 1 · NES | 2 · SNES | 3 · Genesis |
| :---: | :---: | :---: |
| **4 · Update All** | **5 · Brightness** | **6 · Next** |

- Tap Update All to run `/media/fat/Scripts/update_all.sh`. Its running, failed, and finished feedback stays associated with Home even while you browse other pages.
- Tap Brightness for the existing five ascending levels. Hold it for one second to jump to Navigation without changing brightness.
- Press and release Next to cycle through the five pages. Release a held button before using it on the new page.

## Remaining pages

| Page | Top row · 1 / 2 / 3 | Bottom row · 4 / 5 / 6 |
| --- | --- | --- |
| 2 · Consoles | TurboGrafx-16 / PlayStation / Saturn | Nintendo 64 / Mega CD / Next |
| 3 · Consoles | Game Boy Advance / Game Boy / Master System | Neo Geo / The Simpsons / Next |
| 4 · Navigation | Up / Left / Down | Right / Enter / Next |
| 5 · Shortcuts | Menu / Escape / Space | Back to Home / Brightness / Next |

The navigation shortcuts have matching green artwork while held. Back retains the fifth-cycle Stay Puft morph and returns Home on release. Next also shows green while pressed. The original startup mosaic is recomposed for the Mini’s 3×2 layout and fades in and out.

## Install or upgrade

1. Download and extract **MiSTer_StreamDeck_Mini_v1_0_0.zip**.
2. If an earlier launcher is installed, wait for any Update All job to finish and run **StreamDeck_Disable.sh**. Back up your custom configurations.
3. Copy the package’s **Scripts contents** into `/media/fat/Scripts/`, including the hidden **.config** folder. Replace the binary, configurations, and artwork together.
4. Connect the Mini to MiSTer’s USB host hub using its cable; use a data-capable adapter if its connector requires one.
5. Run **StreamDeck_Enable.sh**. The launcher also starts at boot.

**Update All itself is installed separately.** This package installs its first-page button and launcher integration, and expects the updater at `Scripts/update_all.sh`. It does not download or replace your updater. Cores, games, favorites, and BIOS files are also installed separately.

The runtime remains under `/media/fat/Scripts/.config/streamdeck/`. Install one device-specific launcher package there at a time. This Mini package does not drive the 15-key MK.2; the existing MK.2 release remains available separately.

## Configuration and diagnostics

The five files are `buttons.conf`, `buttons-page2.conf`, `buttons-page3.conf`, `buttons-navigation.conf`, and `buttons-shortcuts.conf`. Within each page, `key.0` is physical button 1 and `key.5` is button 6. The additional actions are `next` (cycle pages) and `back` (Home).

**Do not export Mini configurations from the 15-key web editor.** It produces MK.2 layouts and JPEG animations. Edit the Mini configuration files directly for this release; keep a Next or Back action available.

Prepared `.sma` files contain Mini BMP frames. They are not compatible with MK.2 `.sda` files. Original 72×72 character art is centered inside an 80×80 canvas, preserving the existing pixel geometry. Playback uses at least 350 ms per frame to limit USB traffic; slow uploads naturally reduce the frame rate without accumulating frames.

Run `extras/StreamDeck_Diagnostics.sh` over SSH for connection, worker, and updater logs. A missing updater or bad game path is reported through the existing failure feedback. The service retains supervised restart, USB reconnection, held-key rearming, queue clearing on page changes, and bounded image caches.

All five page configurations must load successfully. A failed reload keeps the complete previous configuration set. Update All runs once at a time; Home shows its completion when you return.

## Build and verification

GitHub Actions restores the existing v1 build inputs, generates the current character/control artwork, converts it to Mini format, runs the Mini tests, cross-compiles a static Cortex-A9 ARM binary with Zig 0.13.0, and publishes the ZIP and SHA-256 checksum under the **mini-v1.0.0** release.

The standalone native source is [streamdeck-mini.c](streamdeck-mini.c). `prepare_mini.py` prepares the package; `test_mini.c` and `test_package.py` check the protocol, paging, feedback, cache validation, and first-page updater mapping. The packaged source can be rebuilt with `sh source/build.sh` after installing Zig on a computer.

Supported Mini USB product IDs: `0063`, `0090`, `00B3`, and `00B8`, vendor `0FD9`. The binary rejects unrelated Stream Deck models.

**Hardware validation:** the first Mini release is a host-tested, cross-compiled port. Physical image orientation, brightness, USB playback, keyboard shortcuts, and a complete Update All run still need checking on your Mini and MiSTer. Passing host tests is not a physical-device test.

## Protocol and credits

- [Elgato Mini HID protocol](https://docs.elgato.com/streamdeck/hid/mini/)
- [Upstream python-elgato-streamdeck Mini implementation](https://github.com/abcminiuser/python-elgato-streamdeck/blob/master/src/StreamDeck/Devices/StreamDeckMini.py) and [PIL image transform](https://github.com/abcminiuser/python-elgato-streamdeck/blob/master/src/StreamDeck/ImageHelpers/PILHelper.py), used to cross-check report framing and native BMP orientation.
- Existing launcher, character artwork, and attribution are carried forward from the v1 package. See the included **LICENSE.txt** and **ARTWORK_CREDITS.txt**.
