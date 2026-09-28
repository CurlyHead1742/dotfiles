---
title: Fedora 44 - Unlock Keyring dialog at every login
date: 2026-09-29
machine: nogi-main-rig
tags: [linux, fedora, pam, gnome-keyring, greetd]
---

# Symptom
"Unlock Keyring" dialog ("An application wants access to the keyring
'Default Keyring', but it is locked") at every login. Setup: Fedora 44,
greetd login screen, no autologin.

# Root cause
- Fedora 44 split the PAM module out of `gnome-keyring` into `gnome-keyring-pam`.
- `/etc/pam.d/greetd` lines start with `-` (`-auth optional pam_gnome_keyring.so`),
  which means "skip silently if the module is missing". The missing module
  therefore produced no error.
- Without the module, nothing passed the login password to
  `gnome-keyring-daemon`. It was started by D-Bus / systemd user unit with no
  password, so it stayed locked.

# Diagnosis (read-only)
```bash
pgrep -a gnome-keyring                           # no --login flag = PAM did not start it
grep -r gnome_keyring /etc/pam.d/                # PAM config present
rpm -q gnome-keyring gnome-keyring-pam           # gnome-keyring-pam not installed
ls -l /usr/lib64/security/pam_gnome_keyring.so   # missing
sudo journalctl -b --no-pager | grep -i gkr-pam  # empty = module never ran
dnf provides '*/pam_gnome_keyring.so'            # -> gnome-keyring-pam
```

# Fix
```bash
cp -a ~/.local/share/keyrings ~/keyrings-backup-$(date +%F)   # backup first
sudo dnf install gnome-keyring-pam
# log out fully and log back in
```

# Verification
```bash
sudo journalctl -b --no-pager | grep -i gkr-pam
# expected: "stashed password ...", "unlocked login keyring"
# ("unable to locate daemon control file" in the auth phase is normal)

gdbus call --session --dest org.freedesktop.secrets \
  --object-path /org/freedesktop/secrets/aliases/default \
  --method org.freedesktop.DBus.Properties.Get \
  org.freedesktop.Secret.Collection Locked
# expected: (<false>,)
```

# Result
- PAM created `login.keyring` and unlocked it with the login password.
- `Default_Keyring` (default alias) also unlocks: it shares the login password.
- Dialog gone.

# Notes
- PAM only unlocks keyrings whose password equals the login password.
  After `passwd`, `login.keyring` follows but `Default_Keyring` may not.
  Fix: Seahorse -> right-click keyring -> Change Password.
- The dnf install invalidated a pending offline update transaction
  (dnf5daemon-server). Re-run `sudo dnf upgrade`.
- Backup: `~/keyrings-backup-2026-09-29` (encrypted secrets; delete after a few clean logins).

# References
- https://wiki.archlinux.org/title/GNOME/Keyring
