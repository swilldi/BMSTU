#!/bin/bash

res_file="./func_tests/data/result.txt"
# out_file=${2/out/out_file}
out_file="$2"

# IFS=' ' read -ra args < "$3"

if ./app.exe < "$1" > "$res_file" && ./func_tests/scripts/comparator.sh "$res_file" "$out_file" ; then
    exit 0
else
    exit 1
fi
