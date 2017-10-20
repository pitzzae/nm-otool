#!/bin/bash
#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    test_bin.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/20 20:43:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/10/18 21:24:42 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

FT_NM_PATH="../ft_nm"
FT_OTOOL_PATH="../ft_otool"
GREEN='\033[0;32m' # Green term color
RED='\033[0;31m' # Red term color
NC='\033[0m' # No Color

run_sys_nm () {
	nm $@  2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_nm () {
    $FT_NM_PATH $@ 2>/dev/null | cat -e \
    | sed -e 's/\$/\\n/g'; test ${PIPESTATUS[0]} -ne 0
    STATUS=$?
    if [[ $STATUS -ne 1 ]];
    then
        (>&2 echo -e "${RED}Segfault $FT_NM_PATH $@ exit $STATUS${NC}")
    fi
}

run_sys_otool () {
	otool -t $@ 2>/dev/null | cat -e | sed -e 's/\$/\\n/g'
}

run_ft_otool () {
    $FT_OTOOL_PATH $@ 2>/dev/null | cat -e \
    | sed -e 's/\$/\\n/g'; test ${PIPESTATUS[0]} -ne 0
    STATUS=$?
    if [[ $STATUS -ne 1 ]];
    then
        (>&2 echo -e "${RED}Segfault $FT_OTOOL_PATH $@ exit $STATUS${NC}")
    fi
}

test_diff_output () {
    LEN=$(($LEN + 1))
    TOTAL_TEST=$(($TOTAL_TEST + 2))
    echo -e "Test $@"
    NM=`diff  <(echo -e $(run_sys_nm "$@")) <(echo -e $(run_ft_nm "$@"))`
    OT=`diff  <(echo -e $(run_sys_otool "$@")) <(echo -e $(run_ft_otool "$@"))`
    if [ "$NM" ];
    then
        echo -e "$FT_NM_PATH\t${RED}NOK${NC}"
        (>&2 echo "nm $@")
        (>&2 echo "nm_diff:")
        (>&2 echo "$NM")
        (>&2 echo -e "end_nm_diff\n")
    else
        echo -e "$FT_NM_PATH\t${GREEN}OK${NC}"
        PASS_NM=$(($PASS_NM + 1))
        TOTAL_PASS=$(($TOTAL_PASS + 1))
    fi
    if [ "$OT" ];
    then
        echo -e "$FT_OTOOL_PATH\t${RED}NOK${NC}"
        (>&2 echo "otool $@")
        (>&2 echo "otool_diff:")
        (>&2 echo "$OT")
        (>&2 echo -e "end_otool_diff\n")
    else
        echo -e "$FT_OTOOL_PATH\t${GREEN}OK${NC}"
        PASS_OT=$(($PASS_OT + 1))
        TOTAL_PASS=$(($TOTAL_PASS + 1))
    fi
}

test_path_recur () {
    FILTER="\.bundle\|\.plist\|\.rb\|\.ri\|\.gem\|\.py"
    for LINE in $@/*
    do
        if [[ -d $LINE ]];
        then
           test_path_recur $LINE
        else

            if [ `echo $LINE | grep -v $FILTER` ];
            then
                test_diff_output $LINE
            fi
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

main () {
    RESULT=""
    TOTAL_TEST=0
    TOTAL_PASS=0
    for PATH_TEST in $@
    do
        test_directory "$PATH_TEST/*" 2>error
    done
    echo -e "\n$RESULT"
    echo -e "Result Total $TOTAL_PASS/$TOTAL_TEST\n"
}

time main /usr/bin /usr/lib
