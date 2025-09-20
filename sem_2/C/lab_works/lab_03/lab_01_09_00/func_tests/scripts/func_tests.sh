#!/bin/bash

function run_test
{
    path_data="./../data/"
    type=$1
    test_count=$(ls $path_data | grep -E $type".*in" | wc -l)

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
        
        file_name="$path_data"$file_name
        
        # pwd
        if [ "$type" = "pos" ]; then
            result=$(./pos_case.sh "$file_name"_in.txt "$file_name"_out.txt)
            # cat "$file_name"_in.txt "$file_name"_out.txt
            # echo $result
        elif [ "$type" = "neg" ]; then
            # cat "$file_name"_in.txt
            result=$(./neg_case.sh "$file_name"_in.txt)
        fi

        # echo $result $type
        # echo 1
        if [ "$result" -eq 0 ]; then
            if $verb; then
                echo "$file_name": Success
            fi
        else
            if $verb; then        
                echo "$file_name": Fail            
            fi
            count_failed_test=$((count_failed_test+1))
        fi
    done
}


start_directory=$(pwd)
while [ -z $(pwd | grep -E "lab(_[0-9][0-9]){2,3}$" ) ]; do
    # pwd
    cd ..
done
cd func_tests/scripts



if [ "$1" = "-v" ]; then
    verb=true
else
    verb=false
fi

count_failed_test=0

# обработка позитивных тестов
run_test pos
# обработка негативных тестов
run_test neg


if [ $count_failed_test -eq 0 ]; then
    exit 0
else
    exit $count_failed_test
fi


cd $start_directory