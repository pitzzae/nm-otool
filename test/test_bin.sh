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
	otool -t $@
}

run_ft_otool () {
    $FT_OTOOL_PATH $@
}

test_diff_output () {
    LEN=$(($LEN + 1))
    DIFF=`diff  <(echo -e $(run_sys_nm "$@")) <(echo -e $(run_ft_nm "$@"))`
    if [ "$DIFF" ]
    then
        echo "Test $@"
        echo "nm_diff:"
        echo "$DIFF"
        echo -e "end_nm_diff\n"
        #echo "otool_diff:"
        #diff  <(echo -e $(run_sys_otool "$@")) <(echo -e $(run_ft_otool "$@"))
        #echo -e "end_otool_diff\n"
    else
        echo "Test $@ OK"
        PASS=$(($PASS + 1))
    fi
}

echo "Test /usr/bin/*"
LEN=0
PASS=0
for LINE in /usr/bin/*
do
    test_diff_output $LINE
done
PASSBIN=$PASS
LENBIN=$LEN


echo "Test /usr/lib/*"
LEN=0
PASS=0
for LINE in /usr/lib/*
do
    test_diff_output $LINE
done
PASSLIB=$PASS
LENLIB=$LEN

echo "Result bin $PASSBIN/$LENBIN"
echo "Result lib $PASSLIB/$LENLIB"
