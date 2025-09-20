#!/bin/bash

start_directory=$(pwd)
while [ -z $(pwd | grep -E "lab(_[0-9][0-9]){2,3}$" ) ]; do
    # pwd
    cd ..
done


./build_gcov.sh

cd func_tests/scripts/
./func_tests.sh
cd ../../

gcov main.gcda

if [ "$1" = "-v" ]; then
    cat main.c.gcov
    echo
fi

./clean.sh


cd $start_directory