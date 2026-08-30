# Known Issues And Fast Follows

This file records known non-blocking v0.1 issues without changing working
subsystems during repository construction.

- The source repository has not yet replaced the live `$HOME` worktree.
- External plugin provenance and reproducible build commands still need to be
  recorded per component.
- Optional application integrations require validation on machines without the
  corresponding application installed.
- Plymouth remains source-complete but has not been made part of standard
  deployment.
- Cross-machine monitor and Sunshine behavior requires testing with a second
  hardware profile.

## Targeted Regression Tracking

- Alt+Tab can reportedly advance the wrong monitor. The active path currently
  takes its monitor from `hyprctl activeworkspace.monitor`; it does not use
  `activewindow` or cursor position. Candidates retain a monitor-qualified key,
  but ScrollOverview is opened globally with `open all`, and the workspace
  dispatch carries only the workspace name. Controlled multi-monitor runs,
  including the cursor-opposite-focus case and alternating monitors, did not
  reproduce the failure. The minimal candidate fix is to pin the initiating
  focused monitor for the lifetime of an overview cycle, but this remains
  unimplemented until the compositor/plugin timing that causes the reported
  failure is captured.
- Logout and lock no longer share the same visual choreography. Lock uses
  temporary per-monitor workspaces, Noctalia hide-start, Wallpaper Engine exit,
  and Hyprlock. Logout uses application stashing, Noctalia exit, Wallpaper
  Engine exit, logout sound, and session termination. Logout dry-run restored
  workspaces and application state successfully. This is currently a visual
  parity fast follow and does not block v0.1 unless identical lock/logout
  choreography is a release requirement.
