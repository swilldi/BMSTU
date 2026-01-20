#!/bin/bash

res_file="result.txt"
out_file=${2/out/out_file}

IFS=' ' read -ra args < "$3"

if ./app.exe "${args[@]}" < "$1" > "$res_file" && ./func_tests/scripts/comparator.sh ./func_tests/data/"$res_file" "$out_file" ; then
    exit 0
else
    exit 1
fi
