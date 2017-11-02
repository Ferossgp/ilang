tests=(
    "sum"
    "mul"
)

GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
NORMAL=$(tput sgr0)

declare -i SUCCESFUL_TESTS=0

function test_program {
    llc $1.ll -filetype=obj -o $1.llout 2>&1
    local _ret=$?
    if [ $_ret -ne 0 ] ; then
        return $_ret
    fi
    ../build/voc -o $1.testout $1.voc 2>&1
    cmp -l $1.llout $1.testout 2>&1
}

function run_test {
    printf "$1      \"%s\"   ...\r" $2
    sleep 1
    if testout=$(test_program ${2}); then
        printf "$1      \"%s\"   ${GREEN}passed\n${NORMAL}" $2
        SUCCESFUL_TESTS=$((SUCCESFUL_TESTS + 1))
    else
        printf "$1      \"%s\"   ${RED}failed\n${NORMAL}" $2
    fi
    if ! [ -z "$testout" ]; then
        echo "  " $testout
    fi
}

for i in ${!tests[@]}
do
    run_test $i ${tests[$i]}
done
echo "${SUCCESFUL_TESTS}/${#tests[@]} tests passed"