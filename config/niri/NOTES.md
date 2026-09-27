# Niri (laptop-only, not part of Orbit's Hyprland architecture)

This directory holds a Niri-based alternative session for `nogi-lap` only.
It is **not** part of Orbit's documented architecture (see the top-level
`README.md` and `docs/architecture.md`, which describe the Hyprland +
Noctalia stack that remains authoritative for `nogi-main-rig` and for
Orbit itself).

## Why this exists

`nogi-lap` migrated off KDE Plasma/SDDM. After trying Hyprland (via the
`sdegler/hyprland` COPR), labwc, and Wayfire, this machine settled on
**Niri** — an officially Fedora-packaged compositor, avoiding both the
COPR dependency Hyprland required and the packages Wayfire needed. Login
is handled by `greetd` + `noctalia-greeter`, replacing `plasmalogin`/SDDM.

## Scope

- `config/niri/config.kdl` — this laptop's live Niri config.
- `config/greetd/config.toml` — this laptop's `/etc/greetd/config.toml`,
  configured to run `noctalia-greeter-session`.
- Noctalia's own generated settings (`~/.local/state/noctalia/settings.toml`,
  `state.toml`) are intentionally **not** tracked here, same as they aren't
  tracked anywhere else in this repo — that's generated personal state, not
  authored config. Orbit's existing drop-ins (`config/noctalia/90-orbit-glass.toml`,
  `config/noctalia/hooks.toml`) are shared and untouched by this branch.

## Status

This lives on the `niri-migration` branch, not `main`. No Orbit bootstrap
script, test, or doc has been updated to know about Niri — none of
`bootstrap/deploy`, `bootstrap/migrate`, or `tests/orbit/` apply here.
Deploying this config is currently manual (symlink or copy these files into
place yourself); there is no Niri-aware installer.
