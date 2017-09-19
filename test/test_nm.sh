#!/bin/bash

FT_NM_PATH="../cmake-build-debug/ft_nm"

run_sys_nm () {
	nm $@
}

run_ft_nm () {
    $FT_NM_PATH $@
}

#SYS_NM=$(run_sys_nm $@)
#FT_NM=$(run_ft_nm $@)

#echo "/usr/bin/nm"
#echo "$SYS_NM"

#echo -e "\nft_nm"
#echo "$FT_NM"

#echo -e "\ndiff:"
#diff  <(echo "$SYS_NM" ) <(echo "$FT_NM")

echo -e "\ndiff:"
FILE_TEST="../cmake-build-debug/CMakeFiles/ft_nm.dir/libft/srcs/get_next_line.c.o"
SYS_NM=$(run_sys_nm "$FILE_TEST")
FT_NM=$(run_ft_nm "$FILE_TEST")
diff  <(echo "$SYS_NM" ) <(echo "$FT_NM")