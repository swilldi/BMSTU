#!/bin/bash

res_file="result.txt"

if ./app.exe < "$1" > "$res_file" && ./func_tests/scripts/comparator.sh ./"$res_file" "$2" ; then
    exit 0
else
    exit 1
fi
