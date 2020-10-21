#!/bin/bash
# build some functions

NUM_CPUS=`nproc`
echo "###############"
echo "### Using ${NUM_CPUS} cores"

SRC_DIR=$(pwd)

function fix_arch_ctl()
{
	ARCH=$(dpkg --print-architecture)
    echo "Architecture: ${ARCH}"
	sed '/Architecture/d' -i $1
	test ${ARCH}x == i386x && echo "Architecture: i386" >> $1
	test ${ARCH}x == armhfx && echo "Architecture: armhf" >> $1
	test ${ARCH}x == amd64x && echo "Architecture: amd64" >> $1
	test ${ARCH}x == x86_64x && echo "Architecture: amd64" >> $1
	sed '$!N; /^\(.*\)\n\1$/!P; D' -i $1
}
function dpkg_build()
{
	# Calculate package size and update control file before packaging.
	if [ ! -e "$1" -o ! -e "$1/DEBIAN/control" ]; then exit 1; fi
	sed '/^Installed-Size/d' -i "$1/DEBIAN/control"
	size=$(du -s --apparent-size "$1" | awk '{print $1}')
	echo "Installed-Size: $size" >> "$1/DEBIAN/control"
	dpkg -b "$1" "$2"
}
# build
cd StartPage
cmake .
make "-j${NUM_CPUS}"
# get back to root
cd ..

sed '/Package/d' -i "${SRC_DIR}/files/DEBIAN/control"
sed '/Depends/d' -i "${SRC_DIR}/files/DEBIAN/control"
echo "Package: startpage" >> "${SRC_DIR}/files/DEBIAN/control"
echo "Depends: qt5-default, freerdp2-x11" >> "${SRC_DIR}/files/DEBIAN/control"

mkdir -p files/opt/IT4smart/startpage/StartPage
cp -ar StartPage/StartPage files/opt/IT4smart/startpage/StartPage
cp -ar Ressources files/opt/IT4smart/startpage
fix_arch_ctl "files/DEBIAN/control"
dpkg_build files "${1}-startpage.deb"

# get current version of this package
version=$(awk '/^Version:/ { print $2 }' files/DEBIAN/control)
package=$(awk '/^Package:/ { print $2 }' files/DEBIAN/control)
architecture=$(awk '/^Architecture:/ { print $2 }' files/DEBIAN/control)

mv "${1}-startpage.deb" "${package}_${version}_${architecture}.deb"
