#!/bin/bash


gcc ../../main.c -lm -o ../../app.exe

count_tests=$(($(ls ../data | wc -l) / 2))
count_ok=0
for n in $(seq $count_tests); do
    output=$(echo $(../../app.exe < ../data/pos_0"$n"_in.txt) | grep -Eo "[0-9]+(\.[0-9]+)?")
    good_result=$(cat ../data/pos_0"$n"_out.txt)
    if [[ $output == $good_result ]]; then
        echo test $n: OK
        count_ok=$((count_ok + 1))
    else
        echo result: $output";" good_result: $good_result
        echo test $n: Error
        exit $count_ok
    fi
    
done

