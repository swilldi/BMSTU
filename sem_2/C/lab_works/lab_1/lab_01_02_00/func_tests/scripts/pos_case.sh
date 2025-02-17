#!/bin/bash

input=$1
correct_output=$2

../../app.exe < $input > result_app.txt
if [ $(./comparator.sh ./result_app.txt $correct_output) -eq 0 ]; then
    echo 0
else
    echo 1
fi

