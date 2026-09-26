# Design Intent

This document is the source of truth for what this setup is supposed to
be. It exists so future changes — by me, by Claude, by anyone — get built
against a stated intent instead of being reverse-engineered from whatever
the config currently happens to do. When code and this document disagree,
this document wins, and the code should be fixed to match it.

## Visual identity

- Palette: Catppuccin Mocha as the base, with a violet-emerald accent
  scheme (Mauve-forward).
- Shell: Noctalia.
- Bottom bar: a taskbar showing per-workspace running app instances,
  Windows-taskbar-style (click an icon to focus/restore that window).
- Top bar: date/time, language/layout indicator, quick-settings access.
- Both bars auto-hide.
- Floating dock: a separate element from the bottom taskbar. The dock
  holds pinned/favorite launchers (things you want one click away
  whether or not they're running); the bottom taskbar reflects actually
  running per-workspace app instances. Two different things, both
  wanted, not to be merged into one widget.

## Interaction philosophy

Windows-intuitive keybinds are the goal — not Omarchy's scheme, which
this setup temporarily adopted and is now moving away from. The
authoritative bindings:

| Key | Action |
|---|---|
| Super+C | Close focused window |
| Super+E | File manager |
| Super+B | Browser |
| Super+M | Maximize (windowed — panels/bars stay visible) |
| Super+F | True fullscreen (exclusive, hides bars) |
| Super+Alt+S | Minimize focused window to taskbar |
| Super+S | Peek: show/hide the overlay of all minimized windows |

Super+M and Super+F are deliberately different actions (see the Phase 0
fix) — M is a windowed maximize, F is true exclusive fullscreen. They
must never collapse back into doing the same thing.

## Hard constraints

- Fedora only. No assumption this config works, or should be made to
  work, on any other distro.
- Package sources: official Fedora repos, Flathub, or the KDE Store
  only. No unverified COPRs, no unofficial/third-party repos. (This is
  already the reason WezTerm isn't installed — its COPR had an invalid
  signature — and that should stay the case rather than being worked
  around.)

## Explicitly rejected

- **KDE Plasma** — too GUI-locked; doesn't allow the level of
  customization this setup wants.
- **Omarchy's inherited keybind scheme** — was adopted as a stopgap,
  is being replaced by the Windows-intuitive scheme above.
- **Pure terminal-first workflows** — not the target interaction model
  for this setup.

## Process rule for future work on this config

One setting at a time, verified with a real keypress before moving to
the next. Never simulate window/workspace-state dispatch commands
(fullscreen, move, minimize, focus) as a substitute for a real keypress
— synthetic `hyprctl dispatch` calls have already been shown to behave
differently from actual input at least once (an accidental fullscreen
of the wrong window). Any test that needs real window state gets a
written checklist for a human to run by hand, not something run
unattended.
