# Orbit

Orbit is a reproducible Fedora + Hyprland desktop environment built around
Noctalia, a direct QuickShell global menu, Orbit session utilities, and the
independent Orbit Wallpaper Engine.

This repository contains authored source and deployment logic. It is not a
copy of a home directory. Generated Noctalia and Orbit outputs, monitor
configuration, application state, caches, secrets, compiled plugins, and
external source trees are deliberately excluded.

## Install

Install the documented Fedora and external dependencies first, then run from a
local clone:

```sh
./bootstrap/deploy
./bootstrap/verify
```

Deployment refuses to overwrite an existing unrelated file. It creates
symlinks only for Orbit-owned authored files, seeds mutable configuration only
when absent, enables core user units, and regenerates appearance outputs after
Noctalia is available. It does not perform privileged operations.

Optional integrations are documented separately and are not required for the
core session.

## Architecture

```text
Hyprland
  -> Noctalia
  -> QuickShell global menu
  -> hyprland-session.target
       -> Orbit Wallpaper Engine
       -> workspace and shader services
       -> hypridle and hyprpolkitagent

Noctalia palette/templates
  -> direct GTK, Qt/KDE, WezTerm, and Hyprland outputs
  -> orbit-theme semantic and presentation adapters
  -> Hyprlock adapter
```

Noctalia is the palette authority. Orbit adds only required semantic,
opacity, font, Kitty, and Hyprlock adaptations.

## Monitor Setup

Monitor layout is machine-local and remains owned by `nwg-displays`:

```sh
nwg-displays
```

Do not commit the generated monitor configuration. Orbit discovers connected
monitors at runtime for semantic workspace behavior.

## Validation

```sh
./bootstrap/verify
./tests/orbit/run-all
./tests/orbit/run-all --live
```

Live checks require an active non-root Hyprland session.

## Scope

See `docs/architecture.md`, `docs/dependencies.md`,
`docs/optional-integrations.md`, `docs/deployment.md`, and
`docs/plugins.md` and `docs/known-issues.md` for supported boundaries and
follow-up work.
