#!/bin/bash

# check if script is being run
# or if it's being sourced.
(return 2>/dev/null) && sourced=1 || sourced=0

if (( sourced == 0 ));then
    WORKDIR=$(dirname "$(readlink -f "$0")")
else
    WORKDIR=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
fi

export PATH="${WORKDIR}"/bin:$PATH
TEXT_CONF=$(mktemp)
BINARY_CONF=$(mktemp)
CONFIG="dll \".so\"
module \"${WORKDIR}/module/\"
include \"${WORKDIR}/include/\"
maxstep 0
maxlocalstep 0
maxlevel 29666
maxmem 0
"
echo "$CONFIG" > "${TEXT_CONF}"
scriba -f ${BINARY_CONF} -k ${TEXT_CONF} 2>/dev/null
export SCRIBACONF="${BINARY_CONF}"

if (( sourced == 0 )); then
    scriba $@
    [[ -e "${TEXT_CONF}" ]] && rm "${TEXT_CONF}"
    [[ -e "${BINARY_CONF}" ]] && rm "${BINARY_CONF}"
fi

