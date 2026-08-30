# Generated And Runtime Files

The repository tracks generators and authored templates, not their outputs.

Generated or runtime files include:

- Noctalia Hyprland, GTK, Qt/KDE, WezTerm, and wallpaper-palette outputs;
- Orbit semantic, GTK, Kitty, shape, and Hyprlock adapters;
- `nwg-displays` monitor configuration;
- Wallpaper Engine status, FIFOs, and Hyprlock background output;
- systemd, Noctalia, browser, editor, and test state;
- caches, logs, compiled plugins, and Python bytecode.

The canonical appearance path is:

```text
Noctalia outputs
  -> orbit-update-all-colors noctalia
      -> orbit-theme apply noctalia
          -> semantic.json and active Orbit adapters
          -> Hyprlock adapter
```
