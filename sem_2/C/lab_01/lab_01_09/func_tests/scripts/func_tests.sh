#!/bin/bash

function run_test
{
    # path_data="./../data/"
    type=$1
    tests=$(find ../data/ -regex ".*$type.*in.*")

    if [ -z "$tests" ]; then
        return
    fi

    for in_file in $tests
    do    
        out_file=${in_file/in/out}
        
        # pwd
        if [ "$type" = "pos" ]; then
            result=$(./pos_case.sh "$in_file" "$out_file")
            # cat "$file_name"_in.txt "$file_name"_out.txt
            # echo $result
        elif [ "$type" = "neg" ]; then
            # cat "$file_name"_in.txt
            result=$(./neg_case.sh "$in_file")
        fi

        # echo $result $type
        # echo 1
        if [ "$result" -eq 0 ]; then
            if $verb; then
                echo "${in_file/.*$type/$type}": Success
            fi
        else
            if $verb; then        
                echo "${in_file/.*$type/$type}": Fail            
            fi
            count_failed_test=$((count_failed_test+1))
        fi
    done
}


start_directory=$(pwd)
while ! (pwd | grep -qE "lab(_[0-9][0-9]){2,3}$"); do
    # pwd
    cd .. || exit
done
cd func_tests/scripts || exit



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

cd "$start_directory" || exit

if [ $count_failed_test -eq 0 ]; then
    exit 0
else
    exit $count_failed_test
fi
