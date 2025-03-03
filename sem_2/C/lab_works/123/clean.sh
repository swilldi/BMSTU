#!/bin/bash

start_directory=$(pwd)
while [ -z $(pwd | grep -E "lab(_[0-9][0-9]){2,3}$" ) ]; do
    pwd
    cd ..
done

for type in o exe gcno gcda gcov txt
do
    rm -f *.$type
done

rm func_tests/scripts/*.txt

cd $start_directory



