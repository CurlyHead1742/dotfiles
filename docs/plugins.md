# Plugin Provenance

Compiled plugin files are never committed. The repository should retain the
source provenance and build procedure below.

| Component | Source | Reference observed on this host | Runtime artifact |
|---|---|---|---|
| Hyprglass | `https://github.com/hyprnux/hyprglass.git` | `5bc835dcc909cef6980291688143048cf16942b5` | `hyprglass.so` |
| ScrollOverview | `https://github.com/yayuuu/hyprland-scroll-overview.git` | `f9248ab6bee770e9d68813b48cc6ca12b3271254` | `libscrolloverview.so` |
| Dynamic Cursors | `https://github.com/virtcode/hypr-dynamic-cursors.git` | `5a224284872208b5324759d535d65061043725de` | `dynamic-cursors.so` |
| Oblique Cursor | `https://github.com/kayxean/oblique-cursor.git` | `ecddc552b8a5eb53fbf7498f0e60fbd634906b4a` | Cursor theme assets |
| HyprWindowShade | `https://github.com/ManofJELLO/HyprWindowShade.git` | `40b756befa36cfd5cbed65d554c719141a65c420` | `HyprWindowShade.so` |

HyprWindowShade is built by `bin/install-hyprwindowshade` and receives the
tracked local patch. Build output is installed outside the repository.

The current local Wallpaper Engine checkout has a legacy remote named
`legacy-origin` pointing at the retired PS3 wallpaper repository. This is a
provenance blocker for final reproducibility and must be corrected in the
independent Wallpaper Engine project, not by copying that source here.
