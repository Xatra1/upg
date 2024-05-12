// Header inclusions and definitions
#include <cstdlib>
#include <fstream>
#include <getopt.h>
#include <iostream>
#define no_argument 0
#define required_argument 1
#define optional_argument 2

// Declarations
using namespace std;
int usage(int rcode);
bool verbose = false;

// Print the usage doc and exit with status rcode
int usage(int rcode) {
  cout << R"EOF(upg - automation script for upgrading packages with APT,
Pacman, Flatpak, and Snap. Also performs some other tasks
like initramfs regeneration, GRUB configuration updates,
indexing of the filesystem and clearing of the cache 
memory.

-h, --help, --usage     Prints this help document and
                        terminates the program.

-v, --verbose           Allows some commands to output
                        verbosely.

Report bugs to <https://github.com/Xatra1/upg>
)EOF";
  exit(rcode);
}

int main(int argc, char *argv[]) {
  int index;
  const struct option longopts[] = {
      {"help", no_argument, 0, 'h'},
      {"usage", no_argument, 0, 'h'},
      {"verbose", no_argument, 0, 'v'},
  };
  switch (getopt_long(argc, argv, "hv", longopts, &index)) {
  case 'h':
    usage(0);
    break;
  case 'v':
    cout << "\e[33;1;37mRunning in verbose mode. Supported commands will use "
            "verbose output.\e[0m\n";
    verbose = true;
    break;
  }
  // Used to check if commands exist
  ifstream cmd;
  // Stores user responses
  char ans;
  //
  // APT
  //
  cmd.open("/usr/bin/apt");
  if (cmd) {
    system("sudo dpkg --configure -a");
    cout << "\e[33;1;37mUpdating repositories...\e[0m\n";
    system("sudo apt-get update");
    cout << "\e[33;1;37mUpgrading Debian packages and removing unused "
            "dependencies...\e[0m\n";
    system("sudo apt-get dist-upgrade -y --autoremove --purge");
    cout << "\e[33;1;37mPurging configuration files of previously removed "
            "packages...\e[0m\n";
    system("sudo apt-get purge -y $(dpkg -l | grep '^rc' | awk '{print $2}')");
  } else
    cout << "\e[33;1;37mAPT not found.\e[0m\n";
  cmd.close();
  //
  // Pacman
  //
  cmd.open("/usr/bin/pacman");
  if (cmd) {
    cout << "\e[33;1;37mUpgrading Pacman packages...\e[0m\n";
    if (verbose)
      system("sudo pacman -Syuv");
    else
      system("sudo pacman -Syu");
  } else
    cout << "\e[33;1;37mPacman not found.\e[0m\n";
  cmd.close();
  //
  // Flatpak
  //
  cmd.open("/usr/bin/flatpak");
  if (cmd) {
    cout << "\e[33;1;37mUpgrading Flatpak packages...\e[0m\n";
    if (verbose)
      system("sudo flatpak update -vv --assumeyes");
    else
      system("sudo flatpak update --assumeyes");
  } else
    cout << "\e[33;1;37mFlatpak not found.\e[0m\n";
  cmd.close();
  //
  // Snap
  //
  cmd.open("/usr/bin/snap");
  if (cmd) {
    cout << "\e[33;1;37mUpgrading Snap packages...\e[0m\n";
    system("sudo snap refresh");
    cout << endl;
  } else
    cout << "\e[33;1;37mSnap not found.\e[0m\n";
  cmd.close();
  //
  // Filesystem indexing (updatedb)
  //
  cout << "\e[33;1;37mIndex the filesystem? This can take a very long time. "
          "[y/n]: \e[0m";
  cin >> ans;
  if (ans == 'y') {
    if (verbose)
      system("sudo updatedb -v");
    else
      system("sudo updatedb");
  }
  //
  // Initramfs regeneration (update-initramfs/mkinitcpio)
  //
  cmd.open("/usr/sbin/update-initramfs");
  if (cmd) {
    if (verbose)
      system("sudo update-initramfs -uv");
    else
      system("sudo update-initramfs -u");
  } else {
    cout << "\e[33;1;37mupdate-initramfs not found.\e[0m\n";
    cmd.close();
    cmd.open("/usr/bin/mkinitcpio");
    if (cmd) {
      if (verbose)
        system("sudo mkinitcpio -Pv");
      else
        system("sudo mkinitcpio -P");
    } else
      cout << "\e[33;1;37mmkinitcpio not found.\e[0m\n";
  }
  cmd.close();
  //
  // GRUB configuration updating (grub-mkconfig)
  //
  cout << "\e[33;1;37mUpdating GRUB configuration file...\e[0m\n";
  system("sudo grub-mkconfig -o /boot/grub/grub.cfg");
  //
  // Cache clear (sync, sysctl, rm)
  //
  cout << "\e[33;1;37mSynchronizing cache writes...\e[0m\n";
  system("sync");
  cout << "\e[33;1;37mClearing cache memory...\e[0m\n";
  system("sudo sysctl -w vm.drop_caches=3");
  cout << "\e[33;1;37mRemoving contents of \"~/.cache\"...\e[0m\n";
  if (verbose)
    system("rm -rfv ~/.cache/*");
  else
    system("rm -rf ~/.cache/*");
  cout << "\e[33;1;37mScript completed.\e[0m\n";
  return 0;
}