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

echo -e "\ndiff:"
FILE_TEST="./libft_malloc.dylib"
SYS_NM=$(run_sys_otool "$FILE_TEST")
FT_NM=$(run_ft_otool "$FILE_TEST")
diff  <(echo "$SYS_NM" ) <(echo "$FT_NM")

echo -e "\ndiff:"
FILE_TEST="../cmake-build-debug/CMakeFiles/ft_nm.dir/libft/srcs/get_next_line.c.o"
SYS_NM=$(run_sys_otool "$FILE_TEST")
FT_NM=$(run_ft_otool "$FILE_TEST")
diff  <(echo "$SYS_NM" ) <(echo "$FT_NM")