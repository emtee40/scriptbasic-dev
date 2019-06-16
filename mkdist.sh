#!/bin/bash

DEST="$1"

if [[ -n $DEST ]];then
    mkdir -p "$DEST"/{bin,include,module,lib}
    cp bin/exe/* "$DEST/bin"
    cp bin/lib/* "$DEST/lib"
    cp bin/mod/dll/* "$DEST/module"
    find extensions -name "*.bas" -exec cp {} "$DEST/include" \;
    cp sb.sh "$DEST/sb.sh"
    chmod 755 "$DEST/sb.sh"
else
    printf "\n**WARNING** Missing path to destination folder\n"
    printf  "\nUsage:  $0 <FULL path to destination FOLDER>\n\n"
    printf  "Ex:  ./mkdist.sh ~/Projects/sb\n\n"
fi

