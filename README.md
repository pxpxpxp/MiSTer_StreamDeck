# MiSTer Stream Deck v1

A native MiSTer launcher for the 15-button Elgato Stream Deck MK.2, with
animated console artwork and a second page of keyboard shortcuts.

## Install

Copy the contents of `Scripts/` into `/media/fat/Scripts/`, including the
hidden `.config` folder. Connect the deck using a USB-A–to–USB-C data cable
through MiSTer's USB host hub. Run `StreamDeck_Enable.sh`.

## Two pages

Page 1 contains the console launchers, Simpsons, Update All, and brightness.
Tap button 15 for ascending brightness; hold it for one second for shortcuts.
Page 2 has arrows, Menu, Enter, Space, Escape, and Back. Tap Back to return.

See [the complete instructions](README.txt) and download
[the animated five-page guide](README_Guide_v1.html) to open it in a browser.

## Build and validation

Native source and host tests are in `Scripts/.config/streamdeck/source/`.
The static ARM binary is included. Build with Zig using `source/build.sh`.
See `TWO_PAGES_VALIDATION.txt` for passing checks and hardware testing limits.
Cores, ROMs, BIOS files, and Update All are installed separately.

## Credits

See `LICENSE.txt` and `ARTWORK_CREDITS.txt`. Third-party licensing and required
attribution are retained. The release contains no user-specific configuration.
