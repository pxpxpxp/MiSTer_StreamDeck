Mini v1.0.3 — simpler runtime and packaging

- Use the same hold rules for input handling and scheduling; fix the Home brightness/custom-HOLD conflict.
- Route script feedback directly to its owning page without swapping visible page state.
- Prepare only Mini files instead of copying and discarding the MK.2 tree.
- Define versioned package names and release tags centrally in releases.py.

For both decks, use the [Dual v1.0.1 bundle](https://github.com/pxpxpxp/MiSTer_StreamDeck/releases/tag/dual-v1.0.1). It contains the reviewed MK.2 and Mini binaries, independent services, and shared Update All exclusion. Both-deck controls now attempt both services even if one fails.

Update All remains on Mini Home, physical key 4. Disable the service and back up custom settings before replacing the complete Scripts contents, including hidden .config. Install Update All separately at Scripts/update_all.sh. Physical shared-hub behavior still needs checking on your MiSTer.
