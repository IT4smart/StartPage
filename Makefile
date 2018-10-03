all:
	@echo "Specify a target:\nmake armv6l\nmake armv7\nmake i386\n"
armv6l:
	sudo bash build.sh "armv6l"
armv7:
	sudo bash build.sh "armv7"
i686:
	sudo bash build.sh "i686"
amd64:
	sudo bash build.sh "amd64"
clean:
	sudo rm -f *.deb > /dev/null 2>&1
	sudo rm -rf files/opt/IT4smart/startpage > /dev/null 2>&1
	sudo ./StartPage/clean_cmake.sh
