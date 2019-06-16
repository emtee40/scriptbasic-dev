#!/usr/bin/env bash

ARCH=$(dpkg --print-architecture)
NAME=scriptbasic
VERSION=2.1
OS=$(uname)
MKTMP=$(mktemp -d)
OUTPUT="$NAME-$VERSION-${OS,,}-$ARCH"
DEST="$MKTMP/$OUTPUT/usr/local"

case $ARCH in
	"armfh")
		DEPENDS="libcurl3-gnutls, libiodbc2, libmariadbclient18, libncurses5, libsqlite3-0, libssl1.1";;
	"amd64")
		DEPENDS="libcurl3-gnutls, libiodbc2, libmysqlclient20, libncurses5, libsqlite3-0, libssl1.0.0";;
esac

CONTROL="Package: $OUTPUT
Version: 2.1-1
Architecture: $ARCH
Depends: $DEPENDS
Maintainer: support@scriptbasic.org
Description: Basic Scripting Language
"

CONFIG="dll \".so\"
module \"/usr/local/lib/scriba/\"
include \"/usr/local/include/scriba/\"
maxstep 0
maxlocalstep 0
maxlevel 29666
maxmem 0
"

mkdir -p "$MKTMP/$OUTPUT/DEBIAN"
echo "$CONTROL" > "$MKTMP/$OUTPUT/DEBIAN/control"
echo "ldconfig" > "$MKTMP/$OUTPUT/DEBIAN/postinst"
echo "ldconfig" > "$MKTMP/$OUTPUT/DEBIAN/postrm"
echo "$CONFIG" > "$MKTMP/sb.conf"
chmod a+x "$MKTMP/$OUTPUT/DEBIAN/postinst" "$MKTMP/$OUTPUT/DEBIAN/postrm"

mkdir -p "$DEST"/{bin,include/scriba,lib/scriba}
cp bin/exe/* "$DEST/bin"
cp bin/lib/* "$DEST/lib"
cp bin/mod/dll/* "$DEST/lib/scriba"
find extensions -name "*.bas" -exec cp {} "$DEST/include/scriba" \;

mkdir -p "$MKTMP/$OUTPUT/etc/scriba"
./bin/exe/scriba -f "$MKTMP/$OUTPUT/etc/scriba/basic.conf" -k "$MKTMP/sb.conf" 2>/dev/null

mkdir -p PACKAGES

dpkg --build "$MKTMP/$OUTPUT" 1>/dev/null
mv  "$MKTMP/$OUTPUT.deb" "PACKAGES/$OUTPUT.deb"

[[ -d $MKTMP ]] && rm -r "$MKTMP"
