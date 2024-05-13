# About
This script will utilize the following commands on your system:
- sudo\[*]
- APT/Pacman
- Flatpak
- Snap
- updatedb
- update-initramfs/mkinitcpio
- grub-mkconfig\[*]
- sync\[*]
- sysctl\[*]
- rm\[*]  
  
\[*] - Required.  
Any commands that are not required will be automatically skipped if not found.
### Building from Source
Dependencies:
- g++
- make
- git
- dpkg\[*]  
  
\[*] - Optional.
  
Open a terminal and clone the repo:  
``git clone https://github.com/Xatra1/upg``  
Or clone via SSH:  
``git clone git@github.com:Xatra1/upg``  
  
Then, you need to create the proper directories for the make operation to work.  
``cd`` into the folder that contains the cloned files and run the following:  
``mkdir src/deb/usr && mkdir src/deb/usr/bin``  

After setting up the proper directories, run ``make upg`` to compile the executable.  
  
You then have two options:  
``make build-pkg`` - Builds and installs a Debian package. Requires dpkg.  
``make install`` - Installs the program into the /usr/bin directory.