CC=c++
DIR=src/deb/usr/bin/upg

upg: src/main.cc src/deb/DEBIAN/control
	$(CC) -o $(DIR) src/main.cc

build-pkg:
	dpkg-deb --build src/deb
	sudo dpkg -i src/deb.deb
	
install:
	sudo install src/deb/usr/bin/upg /usr/bin/upg