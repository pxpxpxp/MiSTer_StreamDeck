Mini v1.0.1 — code review fixes

Update All remains on Home, physical key 4 (bottom left).

- Fix idle CPU spinning with custom hold settings and during page transitions.
- Rearm simultaneously held keys after switching pages and clear stale green shortcut images.
- Route script completion to its owning page; retain updater success/failure feedback across USB reconnects.
- Validate the complete page set with relative configuration paths.
- Retry the virtual keyboard after an unavailable/failed uinput connection.
- Add real script guardian, timeout, held-key, page ownership and scheduling regression tests.
- Prioritize press/release feedback, merge duplicate frames and throttle script status polling.
- Restrict USB write access to supported Mini devices, add an advisory device lock and expand USB diagnostics.
- Remove redundant button labels from the Mini guide.

Install all Scripts contents, including hidden .config, after disabling the old launcher and backing up custom configurations. Update All itself remains a separate install at Scripts/update_all.sh.

Built with GitHub Actions as a static Cortex-A9 ARM binary. Host and sanitizer checks do not replace physical Mini/MiSTer testing.

[Mini guide](https://pxpxpxp.github.io/MiSTer_StreamDeck/mini.html) · [Source and installation](https://github.com/pxpxpxp/MiSTer_StreamDeck/tree/main/mini)
