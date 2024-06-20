# About
upg is a very simple shell script designed to automate common tasks related to Linux package managers, along with some extras.<br>

More specifically, this script will do the following:<br>
**apt:**
<br>Finish configuring packages if apt was interrupted prior.
<br>Update repositories.
<br>Upgrade packages and purge unused dependencies
<br>Purge leftover configuration files from previously uninstalled packages.<br>

**Pacman:**
<br>Perform a full system upgrade.

**Flatpak:**
<br>Upgrade all packages.

**Snap:**
<br>Refresh all packages.
<br>Remove disabled packages, such as older revisions of currently installed packages or unused dependencies.<br>
<br>
If you don't have any of the package managers above, don't worry! These operations will be automatically skipped by the script.
<br>

**Misc:**
<br>Rebuild the initrd image. This will first be attempted with update-initramfs, and then with mkinitcpio as a fallback.<br>
Update the GRUB configuration file.<br>
Sync cache writes to the disk.<br>
Drop cache memory.<br>
(Optional) Clear .cache<br>
(Optional) Clear your trash.<br>
(Optional) Update the plocate filesystem index using updatedb.<br>
<br>
If you wish for support to be added for a package manager or an additional task to be automated by the script, file a GitHub issue.

# Installing
You can install the script into the /bin directory using the standard coreutils 'install' command, like so:<br>
``sudo install /path/to/upg /bin``<br>
<br>
Or, you can append the directory to the upg program to your PATH variable.<br>
``export PATH=$PATH:/path/to/upg/parent/directory``<br>
Adding the line above to your .bashrc file will execute it at shell start, allowing upg to be always available!
