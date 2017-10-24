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
FT_OTOOL_PATH="../ft_otool -t"
FILTER="\.bundle\|\.plist\|\.rb\|\.ri\|\.gem\|\.py"
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

clean_progress_bar () {
    printf "\r                                                                                 \r"
}

print_progress_bar () {
    cur=`date +%s`
    runtime=$(( $cur-$start ))
    estremain=$(( ($runtime * $TOTAL_TESTED / $TOTAL_TEST)-$runtime ))
    printf "%d.%d%% complete ($TOTAL_TESTED of $TOTAL_TEST) | %d.%d%% pass ($TOTAL_PASS of $TOTAL_TESTED) - est %d:%0.2d remaining\e[K" \
$(( $TOTAL_TESTED*100/$TOTAL_TEST )) $(( ($TOTAL_TESTED*1000/$TOTAL_TEST)%10)) \
$(( $TOTAL_PASS*100/$TOTAL_TESTED )) $(( ($TOTAL_PASS*1000/$TOTAL_TESTED)%10)) \
$(( $estremain/60 )) \
$(( $estremain%60 ))
}

test_diff_output () {
    LEN=$(($LEN + 1))
    clean_progress_bar
    echo -e "Test $@"
    if [ $TOTAL_TESTED -ne 0 ];
    then
        print_progress_bar
    fi
    NM=`diff  <(echo -e $(run_sys_nm "$@")) <(echo -e $(run_ft_nm "$@"))`
    OT=`diff  <(echo -e $(run_sys_otool "$@")) <(echo -e $(run_ft_otool "$@"))`
    if [ $TOTAL_TESTED -ne 0 ];
    then
        clean_progress_bar
    fi
    if [ "$NM" ];
    then
        echo -e "$FT_NM_PATH\t${RED}NOK${NC}"
        (>>error echo "nm $@")
        (>>error echo "nm_diff:")
        (>>error echo "$NM")
        (>>error echo -e "end_nm_diff\n")
    else
        clean_progress_bar
        echo -e "$FT_NM_PATH\t${GREEN}OK${NC}"
        PASS_NM=$(($PASS_NM + 1))
        TOTAL_PASS=$(($TOTAL_PASS + 1))
    fi
    if [ "$OT" ];
    then
        echo -e "$FT_OTOOL_PATH\t${RED}NOK${NC}"
        (>>error echo "otool $@")
        (>>error echo "otool_diff:")
        (>>error echo "$OT")
        (>>error echo -e "end_otool_diff\n")
    else
        echo -e "$FT_OTOOL_PATH\t${GREEN}OK${NC}"
        PASS_OT=$(($PASS_OT + 1))
        TOTAL_PASS=$(($TOTAL_PASS + 1))
    fi
    TOTAL_TESTED=$((TOTAL_TESTED + 2))
    print_progress_bar
}

test_path_recur () {
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
    echo "Test $@"
    PASS_NM=0
    PASS_OT=0
    LEN=0
    test_path_recur $@
    RESULT="$RESULT""Result [ft_nm] $@ $PASS_NM/$LEN\n"
    RESULT="$RESULT""Result [ft_otool] $@ $PASS_OT/$LEN\n\n"
}

count_path_len () {
    for LINE in $@/*
    do
        if [[ -d $LINE ]];
        then
           count_path_len $LINE
        else
            if [ `echo $LINE | grep -v $FILTER` ];
            then
                TOTAL_TEST=$(($TOTAL_TEST + 2))
                printf "\r%s" $TOTAL_TEST
            fi
        fi
    done
}

count_total_test () {
    echo -e "Find test files"
    if [ $TOTAL_TEST_MANU -ne 0 ];
    then
        TOTAL_TEST=$TOTAL_TEST_MANU
        echo "$TOTAL_TEST"
    else
        for PATH_TEST in $@;
        do
            count_path_len "$PATH_TEST"
        done
    fi
}

manual_test () {
    TOTAL_TEST_MANU=0
    TOTAL_TEST=0
    TOTAL_PASS=0
    TOTAL_TESTED=0
    count_total_test $@
    test_diff_output $@
}

main () {
    RESULT=""
    #TOTAL_TEST_MANU=5282
    TOTAL_TEST_MANU=5282
    TOTAL_TEST=0
    TOTAL_PASS=0
    TOTAL_TESTED=0
    count_total_test $@
    for PATH_TEST in $@
    do
        test_directory "$PATH_TEST" 2>> error
    done
    echo -e "\n$RESULT"
    echo -e "Result Total $TOTAL_PASS/$TOTAL_TEST\n"
}

start=`date +%s`
echo "" > error
time main /usr/bin /usr/lib
