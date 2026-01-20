#!/bin/bash


path_to_data="./func_tests/data/"
res_file=$path_to_data"result.txt"
out_data=$2
out_file=${out_data/out/out_file}


IFS=' ' read -ra args < "$3"

if ./app.exe "${args[@]}" < "$1" > "$res_file" && ./func_tests/scripts/comparator.sh ./"$res_file" "$out_file" ; then
    exit 0
else
    exit 1
fi