#!/bin/bash

# pwd
# echo cp "$in_file" ./work_file.txt

# echo "$1"
# cat "$1"
if ! ./app.exe < "$1"; then
    exit 0
else
    exit 1
fi