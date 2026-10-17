Mini v1.0.4 — ignored button press fix

- Fix a reproduced input-blocking loop on slow animated page changes. Initial page images finish before animation frames resume.
- Read the Mini report ID and six key-state bytes, matching the upstream driver's seven-byte read and avoiding assumptions about padding length.
- Track held keys during startup so they remain suppressed until released after the fade.
- Add input report/press counters and startup/page-transition state to diagnostics. Log only the first 12 presses and first five malformed input reports.

The [Dual v1.0.2 bundle](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/tag/dual-v1.0.2) includes Mini v1.0.4 and the same page-paint protection for MK.2.

Disable the service and back up custom settings before replacing all Scripts contents, including hidden .config. Enable the Mini with StreamDeck_Mini_Enable.sh, or both decks with StreamDeck_Both_Enable.sh. Update All remains on Mini Home/key 4.

Host regression and sanitizer tests cover padded input packets, slow uploads, post-transition presses, held keys and startup tracking. Confirm behavior on your physical Mini and USB hub.
