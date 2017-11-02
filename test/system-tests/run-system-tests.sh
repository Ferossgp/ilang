#!/bin/bash

########################################################################################
# This script runs system tests on the compiler.
# 
# Requirements to run the test
#   1. llc compiler
#   2. voc compiler
# 
# To add new test you need to:
#   1. Add test name to tests array
#   2. Create llvm ir file with expected result under name {TEST_NAME}.ll
#   3. Create .voc file with voc code you want to test under name {TEST_NAME}.voc
#   4. Run this script, specifying path to voc compiler
########################################################################################

# Testcases
tests=(
    "empty_function"
    "arithmetic_int"
    "arithmetic_float"
)

# Output colors
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NORMAL=$(tput sgr0)

# Various useful variables
declare -i SUCCESFUL_TESTS=0
COMPILER_CMD=$1

# Run test given test name
#   1. Runs llc compiler on {TEST_NAME}.ll file
#   2. Runs voc compiler on {TEST_NAME}.voc file
#   3. Dumps both object files using objdum
#   4. Compares resulted dumps
#   5. Clears up results
function test_program {
    local llc_exec=$1.llout
    local voc_exec=$1.vocout

    llc $1.ll -filetype=obj -o $llc_exec 2>&1 > /dev/null
    local _ret=$?
    if [ $_ret -ne 0 ] ; then
        return $_ret
    fi
    ${COMPILER_CMD} -o $voc_exec $1.voc 2>&1 > /dev/null
    local _ret=$?
    if [ $_ret -ne 0 ] ; then
        return $_ret
    fi
    objdump -d $llc_exec 2>&1 | tail -n +3 > f1.dump
    local _ret=$?
    if [ $_ret -ne 0 ] ; then
        rm -f f1.dump
        rm -f f2.dump
        rm -f $llc_exec
        rm -f $voc_exec
        return $_ret
    fi

    objdump -d $voc_exec 2>&1 | tail -n +3 > f2.dump
    if [ $_ret -ne 0 ] ; then
        rm -f f1.dump
        rm -f f2.dump
        rm -f $llc_exec
        rm -f $voc_exec
        return $_ret
    fi

    cmp -l f1.dump f2.dump 2>&1  
    local _ret=$?
    if [ $_ret -ne 0 ] ; then
        rm -f f1.dump
        rm -f f2.dump
        rm -f $llc_exec
        rm -f $voc_exec
        return $_ret
    fi

    rm -f f1.dump
    rm -f f2.dump
    rm -f $llc_exec
    rm -f $voc_exec
    return $_ret    
}

# Runs test case and prints result to stdout 
function run_test {
    printf "%-20s %-20s %-20s\r" "[$1/${#tests[@]}]" "\"${2}\""   "..."
    sleep 1
    if testout=$(test_program ${2}); then
        printf "%-20s %-20s %-20s\n" "[$1/${#tests[@]}]" "\"$2\"" "${GREEN}passed${NORMAL}" 
        SUCCESFUL_TESTS=$((SUCCESFUL_TESTS + 1))
    else
        printf "%-20s %-20s %-20s\n" "[$1/${#tests[@]}]"     "\"${2}\""   "${RED}failed${NORMAL}" 
    fi
    
    if ! [ -z "$testout" ]; then
        echo "  " $testout
    fi
}

# run all test cases
for i in ${!tests[@]}
do
    run_test $(($i+1)) ${tests[$i]}
done

echo "${SUCCESFUL_TESTS}/${#tests[@]} tests passed"
