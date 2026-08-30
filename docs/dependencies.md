# Dependencies

## Direct core runtime

- Fedora Hyprland, Hypridle, Hyprlock, Noctalia, and `hyprpolkitagent`.
- `xdg-desktop-portal` and `xdg-desktop-portal-hyprland`.
- GTK3/GTK4 and Qt6/KDE runtime components.
- `nwg-displays` for machine-local monitor layout.
- systemd user sessions and Wayland.
- Bash, Python 3, `python3-pyudev`, `jq`, `socat`, `flock`, `hyprctl`,
  `dbus-update-activation-environment`, `systemctl`, `sg`, `ps`, `grim`,
  `slurp`, `wl-copy`, `zenity`, `canberra-gtk-play`, and `aplay` or `paplay`.
- Kora icons and the selected GTK theme.

The directly verified Fedora providers on the reference host include:
`hyprland`, `hypridle`, `hyprlock`, `noctalia`, `hyprpolkitagent`,
`nwg-displays`, `xdg-desktop-portal`, `xdg-desktop-portal-hyprland`,
`python3`, `python3-pyudev`, `jq`, `socat`, `util-linux-core`, `shadow-utils`,
`procps-ng`, `grim`, `slurp`, `wl-clipboard`, `zenity`, `libcanberra-gtk3`,
and `alsa-utils`. Some lower-level GTK, Qt, Wayland, and systemd libraries are
transitive dependencies supplied by those packages.

## External runtime components

- QuickShell with the global-menu configuration.
- Hyprglass, HyprWindowShade, ScrollOverview, and Dynamic Cursors plugins.
- Orbit Wallpaper Engine.

These components are not copied into this repository. Their exact provenance
and build instructions belong in the relevant integration documentation.

## Build-only dependencies

Only required when building retained external components:

- `gcc-c++`, `clang`, `lld`;
- `make`, `meson`, `cmake`, `ninja-build`, `pkgconf`, `patch`, and `git`;
- component-specific Hyprland, wlroots, Wayland, EGL/GLES, Cairo, FreeType,
  libpng, Pixman, and libdrm development packages.

## Optional integration dependencies

- Sunshine, Moonlight, and GPU Screen Recorder for streaming.
- Steam and GameMode for game-session behavior.
- Obsidian for the note integration.
- Zen Browser, Zed, WezTerm, Kitty, Nautilus, and their installers for their
  respective optional presentation integrations.
- `nautilus-python`, `python3-gobject`, `procps-ng`, `js-jquery`, and a pinned
  Actions For Nautilus release for Nautilus actions.
- Plymouth script-theme packages for the optional Plymouth integration.
