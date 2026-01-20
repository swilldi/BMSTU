#!/bin/bash

function create_files
{
    if [ "$#" -lt 1 ]; then
        return
    fi


    touch $1"in.txt"
    touch $1"out.txt"
    # touch $1"in_file.txt"

    # touch $1"args.txt"
    # echo "$1""in_file.txt" >> $1"args.txt"
}

start=$(pwd)

cd ./func_tests/data

# Файлы для позитивных тестов
for i in $(seq 1 4); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="pos_"$num"_"
    
    if [ ! -f "$title""in.txt" ]; then
        create_files "$title"
        # touch "$title""out_file.txt"
    fi
    
done

# Файлы для негативных тестов
for i in $(seq 1 6); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="neg_"$num"_"
    if [ ! -f "$title""in.txt" ]; then
        create_files "$title"
    fi

done

cd $start
