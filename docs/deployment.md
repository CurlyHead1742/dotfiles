# Deployment

`bootstrap/deploy` is intentionally small and idempotent.

It:

- creates required destination directories;
- symlinks authored Orbit configuration, scripts, libraries, QuickShell files,
  and user units from this repository;
- seeds mutable Qt configuration only when the destination is absent;
- seeds the Orbit freedesktop sound theme only when its files are absent;
- enables core user services without starting or restarting the desktop;
- asks Noctalia to apply templates and runs the canonical Orbit appearance
  adapter path;
- refuses to replace an existing regular file or unrelated symlink.

The command does not install packages, compile external plugins, modify monitor
configuration, or perform privileged operations. Use the dedicated documented
install steps for those tasks.

Plymouth installation and Noctalia greeter synchronization require privilege
and are separate operations.

To deploy optional user services:

```sh
./bootstrap/deploy --optional
```

Sunshine display recovery additionally requires a machine-local file at
`~/.config/orbit/machine/sunshine-display.conf`, based on
`config/orbit/machine/sunshine-display.conf.example`.
