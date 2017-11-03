#!/bin/bash

PATH_DIR="/Users/gtorresa/Documents/workspace/nm-otool"
FT_NM_PATH="$PATH_DIR/ft_nm"
FT_OTOOL_PATH="$PATH_DIR/ft_otool -t"
FILTER="\.bundle\|\.plist\|\.rb\|\.ri\|\.gem\|\.py"
GREEN='\033[0;32m' # Green term color
RED='\033[0;31m' # Red term color
NC='\033[0m' # No Color
TEST_FILE="$PATH_DIR/libnmotool/libnmotool.a"

get_sig_name () {
    if [ $1 -eq 9 ];
    then
        ERROR="SIGKILL"
    fi
    if [ $1 -eq 11 ];
    then
        ERROR="SIGSEGV segmentation fault"
    fi
}

print_sig_error () {
    ERROR=""
    get_sig_name $2
    echo "Return code $1 $ERROR"

}

head_tail_file () {
    HEAD=`head -c $1 "$PATH_DIR/ft_nm"`
    TAIL=`tail -c+$1 "$PATH_DIR/ft_nm"`
    HEAD=$HEAD$TAIL
    echo $HEAD > "$PATH_DIR/head"
    NM=`$FT_NM_PATH "$PATH_DIR/head" 2>/dev/null`
    RETURN=$?
    CODE_ERR=$(($RETURN - 128))
    if [ $RETURN -gt 2 ];
    then
        echo -e "$RED NOK $NC head -c $1 $PATH_DIR/ft_nm > $FT_NM_PATH head"
        print_sig_error $RETURN $CODE_ERR
        exit
    else
        echo -e "$GREEN OK $NC head -c $1"
    fi
}

head_file () {
    HEAD=`head -c $1 "$PATH_DIR/ft_nm"`
    echo $HEAD > "$PATH_DIR/head"
    NM=`$FT_NM_PATH "$PATH_DIR/head" 2>/dev/null`
    RETURN=$?
    CODE_ERR=$(($RETURN - 128))
    if [ $RETURN -gt 2 ];
    then
        echo -e "$RED NOK $NC head -c $1 $PATH_DIR/ft_nm > $FT_NM_PATH head"
        print_sig_error $RETURN $CODE_ERR
        exit
    else
        echo -e "$GREEN OK $NC head -c $1"
    fi
}

main (){
    SIZE=`ls -la $TEST_FILE | awk '{print $5}'`
    I=0;
    echo -e "Test wrong file:"
    while test $I != $SIZE
    do
        (( I++ ));
        head_file $I
        head_tail_file $I
    done
}

main