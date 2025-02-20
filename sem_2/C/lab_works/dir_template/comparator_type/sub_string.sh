#!/bin/bash

function get_sub_string
{
    # если присутсвует только одно вхождение подстроки
    echo $string | sed "s/.*"$sub_string"[[:space:]]*//"

    # # если присутсвует несколько вхождение подстроки
    # echo $string | sed "s/"$sub_string"[[:space:]]*/\n/; s/.*\n//"
}

content_1=$(get_sub_string $1)
# echo $content_1
content_2=$(get_sub_string $2)
# echo $content_2

if [ "$content_1" = "$content_2" ]; then
    echo 0
else
    echo 1
fi
