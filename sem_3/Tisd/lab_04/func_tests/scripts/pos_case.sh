#!/bin/bash

res_file="./func_tests/data/result.txt"

n=$(echo "$1" | grep -Eo "[0-9][0-9]")
# in_file=func_tests/data/pos_"$n"_in_file.txt
out_file=func_tests/data/pos_"$n"_out.txt

if ./app.exe < "$1" > "$res_file" && ./func_tests/scripts/comparator.sh "$res_file" "$out_file"; then
    exit 0
else
    exit 1
fi

