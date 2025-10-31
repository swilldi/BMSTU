#!/bin/bash
start=$(pwd)
cd ./func_tests/data

count=6
for i in $(seq 1 $count); do 
    if [ $i -lt 10 ]; then
        i="0"$i
    fi

    touch neg_"$i"_in.txt
    # echo neg_"$i"_in_file_1.txt neg_"$i"_in_file_2.txt neg_"$i"_out_file.txt > neg_"$i"_args.txt
done

count=10
for i in $(seq 1 $count); do 
    if [ $i -lt 10 ]; then
        i="0"$i
    fi
    touch  pos_"$i"_in.txt  pos_"$i"_out.txt
    # echo pos_"$i"_in_file_1.txt pos_"$i"_in_file_2.txt pos_"$i"_out_file.txt > pos_"$i"_args.txt
done

cd "$start" || exit
