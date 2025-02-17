#!/bin/bash

# выдает тип и номер теста в формате: <тип>_<номер>
function test_name
{
    echo $1 | grep -Eo -e "pos_[0-9]{2}" -e " neg_[0-9]{2}"
}

# выдает путь к тесту в формате: <path>/<тип>_<номер>
function get_path
{
    if [ "$1" -eq 10 ]; then
        echo  "../data/pos_"$1""
    else
        echo "../data/pos_0"$1""
    fi
}

# очищаем файл для сохрания результатов тестов
echo -n > result_tests.txt

count_test=1
count_failed_test=0
file_path=$(get_path $count_test)
while [ -f $file_path"_in.txt" ]
do
    result=$(./pos_case.sh $file_path"_in.txt" $file_path"_out.txt")
    # echo $result
    if [ $result -eq 0 ]; then
        echo "$(test_name $file_path): Success" >> result_tests.txt
    else        
        echo "$(test_name $file_path): Fail" >> result_tests.txt
        count_failed_test=$((count_failed_test+1))
    fi
    count_test=$((count_test+1))
    file_path=$(get_path $count_test)
done

if [ $count_failed_test -eq 0 ]; then
    exit 0
else
    exit $count_failed_test
fi

