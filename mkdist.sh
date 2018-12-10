#!/bin/bash

DEST="$1"

if [[ -n $DEST ]];then
    mkdir -p "$DEST"/{bin,include,module,lib}
    cp bin/exe/* "$DEST/bin"
    cp bin/lib/* "$DEST/lib"
    cp bin/mod/dll/* "$DEST/module"
    find extensions -name "*.bas" -exec cp {} "$DEST/include" \;
fi


