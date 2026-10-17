Mini v1.0.2 — independent installation and dual-deck support

The Mini now uses Scripts/.config/streamdeck-mini, StreamDeck_Mini_Enable.sh / StreamDeck_Mini_Disable.sh, independent boot markers and /tmp/mister_streamdeck_mini.* logs and locks. The six-key layout and first-page Update All button (physical key 4) remain intact.

To use a Mini and 15-key MK.2 simultaneously, install the [Dual v1.0.0 combined bundle](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/tag/dual-v1.0.0) and run StreamDeck_Both_Enable.sh. It includes both native ARM binaries and coordinates Update All across the two services.

IMPORTANT: Mini v1.0.0/v1.0.1 occupied the MK.2 directory. Disable the old service with StreamDeck_Disable.sh and back up settings before copying the new package. Restore Mini settings into streamdeck-mini only.

The build tests simultaneous host services, independent shutdown and boot blocks, updater exclusion in both directions, Mini sanitizers and MK.2 regression checks. Physical two-deck USB power, timing and controller coexistence need checking on your MiSTer.
