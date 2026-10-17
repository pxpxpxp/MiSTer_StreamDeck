Six-key Stream Deck Mini port of the existing native MiSTer launcher.

**Update All is on Home, physical key 4 (bottom left).** Home also has NES, SNES, Genesis, Brightness, and Next. Five pages retain the other consoles, keyboard navigation, and shortcuts.

- Native Mini USB device detection, input reports, image packets, and brightness control.
- Prepared 80×80 BMP animation frames; cached playback without runtime image decoding.
- Green held shortcut feedback, fifth-cycle Stay Puft Back morph, and the fading startup mosaic.
- Update All running/finished feedback remains on Home while other pages are open.
- Host protocol, paging, malformed-asset, cache, updater-target and sanitizer checks; static ARM cross-compilation in Actions.

Install the Mini package's complete Scripts contents, including hidden .config, into /media/fat/Scripts after disabling the old launcher. Keep the existing updater at Scripts/update_all.sh; the package installs its button, not the updater itself. The 15-key web editor exports are not compatible with this Mini package.

This is the first Mini hardware-test build. Host tests and compilation do not verify physical image orientation, brightness, USB playback or a complete updater run on your Mini. The 15-key MK.2 release remains separate.

[Mini guide](https://pxpxpxp.github.io/MiSTer_StreamDeck/mini.html) · [Mini source and instructions](https://github.com/pxpxpxp/MiSTer_StreamDeck/tree/main/mini)
