#!/bin/bash

start=$(pwd)

cd /Users/dmitriy/BMSTU/sem_3/C/lab_06_01/func_tests/data

# Файлы для позитивных тестов
for i in $(seq 1 15); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="pos_"$num"_"
    touch $title"in.txt"
    touch $title"out.txt"
    touch $title"args.txt"
done

# Файлы для негативных тестов
for i in $(seq 1 5); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="neg_"$num"_"
    touch $title"in.txt"
    touch $title"out.txt"
    touch $title"args.txt"
done

cd $start
