#!/bin/bash

n=$(echo "$1" | grep -Eo "[0-9][0-9]")
in_file=func_tests/data/pos_"$n"_in_file.txt
# pwd
# echo cp "$in_file" ./work_file.txt


if ! ./app.exe < "$1" > /dev/null; then
    exit 0
else
    exit 1
fi