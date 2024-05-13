BIN=src/deb/usr/bin/upg
INS_DIR=/usr/bin/upg
DEB_DIR=src/deb
CONTROL_FILE=src/deb/DEBIAN/control

upg: src/main.cc 
	c++ -o $(BIN) src/main.cc

build-pkg: $(CONTROL_FILE) $(BIN)
	@echo -e '\e[33;1;37mBuilding and installing a package for upg...\e[0m'
	dpkg-deb --build $(DEB_DIR)
	sudo dpkg -i $(DEB_DIR).deb
	
install: $(BIN)
	@echo -e '\e[33;1;37mInstalling upg using generic install command...\e[0m'
	sudo install $(BIN) $(INS_DIR)