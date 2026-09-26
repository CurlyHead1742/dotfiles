#!/usr/bin/env bash
# Super+M: smart minimize/maximize toggle. If the focused window isn't
# fullscreen, maximize it (same action as Super+F). If it's already
# fullscreen, minimize it instead — reuses the same special-workspace
# toggle as Super+S, so it un-minimizes via the same overlay/taskbar icon.
set -euo pipefail

fullscreen=$(hyprctl activewindow -j | jq -r '.fullscreen // 0')

if [[ "$fullscreen" == "0" ]]; then
    hyprctl dispatch --quiet "hl.dsp.window.fullscreen({ mode = \"fullscreen\", action = \"toggle\" })"
else
    exec "$HOME/.config/hypr/scripts/minimize-window"
fi
