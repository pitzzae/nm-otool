#!/bin/bash

FT_OTOOL_PATH="../cmake-build-debug/ft_otool"

run_sys_otool () {
	otool -t $@
}

run_ft_otool () {
    $FT_OTOOL_PATH $@
}

SYS_OTOOL=$(run_sys_otool $@)
FT_OTOOL=$(run_ft_otool $@)

#echo "/usr/bin/otool -t"
#echo "$SYS_OTOOL"

#echo -e "\nft_otool"
#echo "$FT_OTOOL"

echo -e "\ndiff:"
diff  <(echo "$SYS_OTOOL" ) <(echo "$FT_OTOOL")
