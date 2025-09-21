#!/bin/bash

res_file="./func_tests/data/result.txt"
work_file="work_file.txt"

IFS=' ' read -ra args < "$3"
n=$(echo "$1" | grep -Eo "[0-9][0-9]")
in_file=func_tests/data/pos_"$n"_in_file.txt
out_file=func_tests/data/pos_"$n"_out_file.txt

if ./app.exe "${args[@]}" < "$1" > /dev/null && ./func_tests/scripts/comparator.sh "$res_file" "$out_file"; then
    exit 0
else
    exit 1
fi

