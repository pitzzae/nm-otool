#!/bin/bash

FT_NM_PATH="../ft_nm"
FT_OTOOL_PATH="../ft_otool"

run_sys_nm () {
	nm $@ | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_nm () {
    $FT_NM_PATH $@ | cat -e | sed -e 's/\$/\\n/g'
}

run_sys_otool () {
	otool -t $@
}

run_ft_otool () {
    $FT_OTOOL_PATH $@
}

test_diff_output () {
    echo "Test $@"
    echo "nm_diff:"
    diff  <(echo -e $(run_sys_nm "$@")) <(echo -e $(run_ft_nm "$@"))
    echo -e "end_nm_diff\n"
    echo "otool_diff:"
    diff  <(echo -e $(run_sys_otool "$@")) <(echo -e $(run_ft_otool "$@"))
    echo -e "end_otool_diff\n"
}

if [ $1 ]
then
    test_diff_output $@
else
    test_diff_output "/usr/bin/time"
    test_diff_output "./libft_malloc.dylib"
    test_diff_output "libft_malloc_x86_64_Darwin.so"
    test_diff_output "../libft/libft.a"
    test_diff_output "../ft_nm"
    test_diff_output "../ft_otool"
    test_diff_output "./dst/*"
    test_diff_output "./test_nmotool.sh"
    test_diff_output "./wrong_path"
    test_diff_output "./dst"
    test_diff_output
fi
