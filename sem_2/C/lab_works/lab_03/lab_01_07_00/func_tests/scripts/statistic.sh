#!/bin/bash

function print_result
{
    echo -n $1
    current_len=$(echo -n $1 | wc -m)
    add_len=$(($BORDER_LEN-current_len))
    for i in $(seq $add_len)
    do
        echo -n " "
    done
    echo "|"
}

function percent_completed
{
    if [ "$2" -eq 0 ]; then
        echo "100%"
    else
        echo $(($1*100/$2))%
    fi
}

BORDER="-----------------------------|"
BORDER_LEN=$(($(echo -n $BORDER | wc -m) - 1))
# echo $BORDER_LEN

count_pos=0
count_pos_success=0
count_neg=0
count_neg_success=0

echo $BORDER

OLD_IFS=$IFS
IFS=$'\n'
for result in $(cat ./result_tests.txt)
do
    print_result $result
    if [ $(echo "$result" | grep "pos") ]; then
        count_pos=$((count_pos+1))
        if [ $(echo "$result" | grep -i "success") ]; then
            count_pos_success=$((count_pos_success+1))
        fi
    elif [ $(echo "$result" | grep "neg") ]; then
        count_neg=$((count_neg+1))
        if [ $(echo "$result" | grep -i "success") ]; then
            count_neg_success=$((count_neg_success+1))
        fi
    fi
done


echo $BORDER
res_pos="Result pos_test: "$count_pos_success"/"$count_pos" – "$(percent_completed $count_pos_success $count_pos)
print_result $res_pos
res_neg="Result neg_test: "$count_neg_success"/"$count_neg" – "$(percent_completed $count_neg_success $count_neg)
print_result $res_neg
echo $BORDER

IFS=$OLD_IFS