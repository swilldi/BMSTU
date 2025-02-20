#!/bin/bash

function run_test
{
    type=$1
    test_count=$(ls ../data | grep -E $type".*in" | wc -l)

    if [ "$test_count" -eq 0 ]; then
        return
    fi

    for i in $(seq $test_count)
    do
        if [ "$i" -lt 10 ]; then
            file_name=$type"_0"$i
        else
            file_name=$type"_"$i
        fi
        
        if [ $type = "pos" ]; then
            result=$(./pos_case.sh ../data/"$file_name"_in.txt ../data/"$file_name"_out.txt)
        elif [ $type = "neg" ]; then
            result=$(./neg_case.sh ../data/"$file_name"_in.txt)
        fi

        # echo $result $type
        if [ $result -eq 0 -a $verb ]; then
            echo "$file_name": Success >> result_tests.txt
        else
            if [ $verb ]; then        
                echo "$file_name": Fail >> result_tests.txt
            fi
            count_failed_test=$((count_failed_test+1))
        fi
    done
}


if [ "$1" = "-v" ]; then
    verb=True
fi

count_failed_test=0

# обработка позитивных тестов
run_test pos
# обработка негативных тестов
run_test neg

if [ $verb ]; then
    ./statistic.sh
fi

rm *.txt

if [ $count_failed_test -eq 0 ]; then
    exit 0
else
    exit $count_failed_test
fi