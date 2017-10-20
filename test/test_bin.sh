#!/bin/bash

FT_NM_PATH="../ft_nm"
FT_OTOOL_PATH="../ft_otool"

run_sys_nm () {
	nm $@  2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_nm () {
    $FT_NM_PATH $@ 2>/dev/null | cat -e | sed -e 's/\$/\\n/g'; test ${PIPESTATUS[0]} -ne 0
    STATUS=$?
    if [[ $STATUS -ne 1 ]];
    then
        (>&2 echo "Segmentation Fault $FT_NM_PATH $@ exit $STATUS")
    fi
}

run_sys_otool () {
	otool -t $@ 2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_otool () {
    $FT_OTOOL_PATH $@ 2>/dev/null | cat -e | sed -e 's/\$/\\n/g'; test ${PIPESTATUS[0]} -ne 0
    STATUS=$?
    if [[ $STATUS -ne 1 ]];
    then
        (>&2 echo "Segmentation Fault $FT_OTOOL_PATH $@ exit $STATUS")
    fi
}

test_diff_output () {
    LEN=$(($LEN + 1))
    NM=`diff  <(echo -e $(run_sys_nm "$@")) <(echo -e $(run_ft_nm "$@"))`
    OT=`diff  <(echo -e $(run_sys_otool "$@")) <(echo -e $(run_ft_otool "$@"))`
    if [ "$NM" ];
    then
        (>&2 echo "Test nm $@")
        (>&2 echo "nm_diff:")
        (>&2 echo "$NM")
        (>&2 echo -e "end_nm_diff\n")
    else
        echo "Test nm $@ OK"
        PASS_NM=$(($PASS_NM + 1))
    fi
    if [ "$OT" ];
    then
        (>&2 echo "Test otool $@")
        (>&2 echo "otool_diff:")
        (>&2 echo "$OT")
        (>&2 echo -e "end_otool_diff\n")
    else
        echo "Test $@ OK"
        PASS_OT=$(($PASS_OT + 1))
    fi
}

test_path_recur () {
    for LINE in $@/*
    do
        if [[ -d $LINE ]];
        then
           test_path_recur $LINE
        else
            test_diff_output $LINE
        fi
    done
}

test_directory () {
    echo "Test $@/*"
    PASS_NM=0
    PASS_OT=0
    LEN=0
    test_path_recur $@
    RESULT="$RESULT""Result [ft_nm] $@/* $PASS_NM/$LEN\n"
    RESULT="$RESULT""Result [ft_otool] $@/* $PASS_OT/$LEN\n\n"
}

RESULT=""

test_directory /usr/bin 2>error
test_directory /usr/lib 2>error

echo -e "\n$RESULT"
