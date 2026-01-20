#!/bin/bash

start_directory=$(pwd)
while ! (pwd | grep -qE "lab(_[0-9][0-9]){2,3}$"); do
    # pwd
    cd .. || exit
done


./build_gcov.sh

./func_tests/scripts/func_tests.sh -q

gcov ./*.gcda

if [ "$1" = "-v" ]; then
    cat ./*.c.gcov
    echo
fi

./clean.sh

cd "$start_directory" || exit