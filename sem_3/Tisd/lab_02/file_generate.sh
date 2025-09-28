#!/bin/bash

start=$(pwd)

cd ./func_tests/data

# Файлы для позитивных тестов
for i in $(seq 2 13); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="pos_"$num"_"
    touch $title"in.txt"
    touch $title"out.txt"
    # echo "$title""in_file.txt ""$title""out_file.txt" > $title"args.txt"
    touch $title"in_file.txt"
    echo "./func_tests/data/"$title"in_file.txt" > $title"in.txt"
    echo "Renault;4;1;500;White;0;;2007;91573;1;14
Ford;4;0;50000;Black;0;;2024;175272;3;4
Mercedes;9;1;300;Green;0;;1996;79024;3;5
BYD;1;0;5066;Black;0;;1999;273554;2;17
Fiat;6;;200;Green;0;;2024;16529;1;0
Renault;2;1;2000;Yellow;1;3;;;;
Fiat;7;1;66900;Silver;1;5;;;;
BYD;1;0;6000;Orange;0;;2007;208471;3;20" > touch $title"in_file.txt"
    
    # touch $title"out_file.txt"
done

# Файлы для негативных тестов
for i in $(seq 14 20); do
    if [ $i -ge 10 ]; then
        num=$i
    else
        num=0"$i"
    fi
    
    title="neg_"$num"_"
    touch $title"in.txt"
    touch $title"in_file.txt"
done

cd $start
