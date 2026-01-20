#!/bin/bash
start=$(pwd)
cd ./func_tests/data

count=16
for i in $(seq 1 $count); do 
    touch neg_"$i"_args.txt neg_"$i"_in.txt neg_"$i"_in_file_1.txt neg_"$i"_in_file_2.txt neg_"$i"_out_file.txt
    echo neg_"$i"_in_file_1.txt neg_"$i"_in_file_2.txt neg_"$i"_out_file.txt > neg_"$i"_args.txt
done

count=7
for i in $(seq 1 $count); do 
    touch pos_"$i"_args.txt pos_"$i"_in.txt pos_"$i"_in_file_1.txt pos_"$i"_in_file_2.txt pos_"$i"_out.txt pos_"$i"_out_file.txt
    echo pos_"$i"_in_file_1.txt pos_"$i"_in_file_2.txt pos_"$i"_out_file.txt > pos_"$i"_args.txt
done

cd "$start" || exit
