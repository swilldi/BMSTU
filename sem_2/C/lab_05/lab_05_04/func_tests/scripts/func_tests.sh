#!/bin/bash

function run_test
{
    # path_data="./../data/"
    type=$1
    tests=$(find ./func_tests/data/ -regex ".*$type.*in.txt" | sort)

    if [ -z "$tests" ]; then
        return
    fi

    for in_data in $tests
    do  
        out_data=${in_data/in/out}
        args_file=${in_data/in/args}
        
        # pwd
        if [ "$type" = "pos" ]; then
            ./func_tests/scripts/pos_case.sh "$in_data" "$out_data" "$args_file"
            # cat "$file_name"_in.txt "$file_name"_out.txt
            # echo $result
        elif [ "$type" = "neg" ]; then
            # cat "$file_name"_in.txt
            ./func_tests/scripts/neg_case.sh "$in_data" "$args_file"
        fi
        rc="$?"

        # echo 1
        test_name=$(echo "$in_data" | grep -Eo "(pos)?(neg)?_[0-9]{2}")
        if [ "$rc" -eq "0" ]; then
            if $verb; then
                echo "$test_name": Success"  |"
            fi
        else
            if $verb; then
                echo "$test_name": Fail"     |"
            fi
            count_failed_test=$((count_failed_test+1))
        fi
    done
}

function table_top
{
    if ! $verb; then
        return 
    fi

    if [ "$1" = "pos" ]; then
        label="POS"
    else
        label="NEG"
    fi

    echo "-----------------|"
    echo "----""$label""_TESTS----|"
}

function table_bottom
{   
    if ! $verb; then
        return 
    fi

    echo "-----------------|"
}

start_directory=$(pwd)
while ! (pwd | grep -qE "lab(_[0-9][0-9]){2,3}$"); do
    # pwd
    cd .. || exit
done

if [ "$1" == "-q" ]; then
    verb=false
else
    verb=true
fi

count_failed_test=0

table_top pos
# обработка позитивных тестов
run_test pos
table_bottom

table_top neg
# обработка негативных тестов
run_test neg
table_bottom

cd "$start_directory" || exit

if [ $count_failed_test -eq 0 ]; then
    exit 0
else
    exit $count_failed_test
fi
