#!/bin/bash

start_directory=$(pwd)
while [ -z "$(pwd | grep -E "lab(_[0-9][0-9]){2,3}$")" ]; do
    # pwd
    cd .. || exit
done


./build_gcov.sh

cd func_tests/scripts/ || exit
./func_tests.sh
cd ../../ || exit

gcov *.gcda

if [ "$1" = "-v" ]; then
    cat *.c.gcov
    echo
fi

./clean.sh


cd "$start_directory" || exit