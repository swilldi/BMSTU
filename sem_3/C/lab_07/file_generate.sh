#!/bin/bash

start=$(pwd)

cd ./func_tests/data

# Файлы для позитивных тестов
for i in $(seq 1 13); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="pos_"$num"_"
    touch $title"in.txt"
    touch $title"out.txt"
    echo "$title""in_file.txt ""$title""out_file.txt" > $title"args.txt"
    touch $title"in_file.txt"
    touch $title"out_file.txt"
done

# Файлы для негативных тестов
for i in $(seq 1 6); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="neg_"$num"_"
    touch $title"in.txt"
    echo "$title""in_file.txt ""$title""out_file.txt" > $title"args.txt"
    # touch $title"out_file.txt"
done

cd $start
