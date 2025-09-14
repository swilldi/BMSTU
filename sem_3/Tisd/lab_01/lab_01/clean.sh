#!/bin/bash

start_directory=$(pwd)
while ! (pwd | grep -qE "lab(_[0-9][0-9]){1,3}$"); do
     pwd
    cd .. || exit
done

for type in o gcno gcda gcov txt out exe bin
do
    rm -f ./*.$type
done

rm -f func_tests/scripts/*.txt

cd "$start_directory" || exit 



