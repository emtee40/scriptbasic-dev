#!/bin/bash

APT=$(which appimagetool)

[[ -z $APT ]] && echo "Missing appimagetool" && exit 1

DEST=$(mktemp -d)

if [[ -n $DEST ]];then
    mkdir -p "$DEST"/usr/{bin,include,module,lib}
    cp appimage_files/* "$DEST"
    cp bin/exe/* "$DEST/usr/bin"
    cp bin/lib/* "$DEST/usr/lib"
    cp bin/mod/dll/* "$DEST/usr/module"
    find extensions -name "*.bas" -exec cp {} "$DEST/usr/include" \;
    mkdir -p "PACKAGES"
    "$APT" "$DEST" "$PWD/PACKAGES/sb.AppImage"
    [[ -d "$DEST" ]] && rm -r "$DEST"
else
    printf "\n**WARNING** Missing path to destination folder\n"
    printf  "\nUsage:  $0 <FULL path to destination FOLDER>\n\n"
    printf  "Ex:  ./mkdist.sh ~/Projects/sb\n\n"
fi

