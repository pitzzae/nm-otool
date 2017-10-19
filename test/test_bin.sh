#!/bin/bash

FT_NM_PATH="../ft_nm"
FT_OTOOL_PATH="../ft_otool"

run_sys_nm () {
	nm $@  2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_nm () {
    $FT_NM_PATH $@  2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_sys_otool () {
	otool -t $@ 2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_otool () {
    $FT_OTOOL_PATH $@ 2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

test_diff_output () {
    LEN=$(($LEN + 1))
    NM=`diff  <(echo -e $(run_sys_nm "$@")) <(echo -e $(run_ft_nm "$@"))`
    OT=`diff  <(echo -e $(run_sys_otool "$@")) <(echo -e $(run_ft_otool "$@"))`
    if [ "$NM" ]
    then
        echo "Test $@"
        echo "nm_diff:"
        echo "$NM"
        echo -e "end_nm_diff\n"
    else
        echo "Test nm $@ OK"
        PASS_NM=$(($PASS_NM + 1))
    fi
    if [ "$OT" ]
    then
        echo "Test otool $@"
        echo "otool_diff:"
        echo "$OT"
        echo -e "end_otool_diff\n"
    else
        echo "Test $@ OK"
        PASS_OT=$(($PASS_OT + 1))
    fi
}

echo "Test /usr/bin/*"
PASS_NM=0
PASS_OT=0
LEN=0
for LINE in /usr/bin/*
do
    test_diff_output $LINE
done
PASSBIN_NM=$PASS_NM
PASSBIN_OT=$PASS_OT
LENBIN=$LEN

echo "Test /usr/lib/*"
PASS_NM=0
PASS_OT=0
LEN=0
for LINE in /usr/lib/*
do
    test_diff_output $LINE
done
PASSLIB_NM=$PASS_NM
PASSLIB_OT=$PASS_OT
LENLIB=$LEN

echo "Result [ft_nm] bin $PASSBIN_NM/$LENBIN"
echo "Result [ft_otool] bin $PASSBIN_OT/$LENBIN"
echo "Result [ft_nm] lib $PASSLIB_NM/$LENLIB"
echo "Result [ft_otool] lib $PASSLIB_OT/$LENLIB"
