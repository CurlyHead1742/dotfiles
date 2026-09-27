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

## Session log — 2026-09-27/28: Qt6 dark theme + cross-machine git audit

- Added an `environment {}` block to `config.kdl` setting
  `QT_QPA_PLATFORMTHEME=qt6ct` (commit `d462ed7`). Qt6 apps (Discover, etc.)
  weren't inheriting the theme without it. qt6ct itself was already
  correctly configured (custom palette -> `noctalia.colors`).
- `niri msg action reload-config` does **not** re-export `environment {}`
  vars into the systemd/dbus activation environment — that only happens
  at niri's own startup. A full logout/login (or manual
  `systemctl --user set-environment` + `dbus-update-activation-environment`)
  is required for already-running/dbus-activated apps to pick up a new
  `environment {}` value.
- Separately, `~/.config/discoverrc` was trimmed from
  `Sources=flathub,fedora,fedora-testing` to `Sources=flathub` (removed two
  stale entries that were never real `flatpak remotes` on this machine —
  cosmetic-only, nothing installed was affected). **This file is not
  tracked in this repo** and `bootstrap/deploy` does not manage it — it's
  a manual, per-machine edit only, currently applied to `nogi-lap` only.
- App-launcher clutter (KDE Connect Indicator, KDebugSettings, drkonqi
  coredump viewer, SELinux Troubleshooter, GnuPG Log Viewer, import
  wizards, etc. showing in Noctalia's app search) — not fixed via any
  Noctalia setting (checked `[shell.launcher]` in
  `~/.local/state/noctalia/settings.toml`; no hide-list exists there).
  The fix is per-app `NoDisplay=true` overrides in
  `~/.local/share/applications/`, not yet applied as of this log entry.

### Git state at time of this entry (for cross-machine comparison)

- `niri-migration` was 1 commit ahead of `origin/niri-migration`
  (`d462ed7`, the QT_QPA_PLATFORMTHEME fix) — **not yet pushed**.
- `labwc-trial` and `laptop-0926` exist **only on `nogi-lap`**, never
  pushed to origin. `laptop-0926`'s one commit not otherwise reachable
  (`7e42aca`, "Fix Super+M maximize...") is a byte-identical patch to
  `niri-migration`'s `6a6d268` — same fix, different hash from being
  rebased onto a different tip. Not real drift.
- `config/niri/noctalia.kdl` is intentionally `.gitignore`d — Noctalia
  regenerates it per-machine from the active palette; it will differ
  file-for-file between `nogi-lap` and `nogi-main-rig` by design.
- Before deploying this branch to `nogi-main-rig`, `d462ed7` needs to be
  pushed (a machine can't `git pull` a commit that only exists locally on
  `nogi-lap`); whether `labwc-trial`/`laptop-0926` get pushed too, and
  whether `discoverrc` gets folded into this repo's `bootstrap/deploy`,
  were left as open decisions as of this entry.
