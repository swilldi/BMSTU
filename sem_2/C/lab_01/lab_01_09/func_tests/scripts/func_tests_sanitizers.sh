#!/bin/bash

function result_output
{
    if [ "$1" -eq 0 ]; then
        echo OK
    else
        echo FAIL
    fi
}

start_directory=$(pwd)
while ! (pwd | grep -qE "lab(_[0-9][0-9]){2,3}$"); do
    # pwd
    cd .. || exit
done

if [ "$1" == "-v" ]; then
    verb=true
else
    verb=false
fi

sanitizers=$(find . -regex "./build_debug_.*\.sh")
fail_count=0

for builder in $sanitizers
do 
    ./clean.sh
    ./"$builder"
    ./func_tests/scripts/func_tests.sh
    res=$?
    fail_count=$((fail_count + res))

    if $verb; then
        echo "${builder/\.\/build/build}: $(result_output $res)"
    fi

done

cd "$start_directory" || exit 

exit $fail_count