#!/usr/bin/env bash
# Super+M: smart minimize/maximize toggle. If the focused window isn't
# already maximized or fullscreen, maximize it (windowed — panels/bars
# stay visible; distinct from Super+F's true fullscreen). If it's
# already maximized/fullscreen, minimize it instead — reuses the same
# minimize-window script as Super+Alt+S.
set -euo pipefail

fullscreen=$(hyprctl activewindow -j | jq -r '.fullscreen // 0')

if [[ "$fullscreen" == "0" ]]; then
    hyprctl dispatch --quiet "hl.dsp.window.fullscreen({ mode = \"maximized\", action = \"toggle\" })"
else
    exec "$HOME/.config/hypr/scripts/minimize-window"
fi
