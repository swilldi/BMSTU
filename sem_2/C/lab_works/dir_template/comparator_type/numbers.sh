#!/bin/bash

function get_numbers
{
    cat $1 | grep -Eo "[-]?[1-9][0-9]*(\.[0-9]*[1-9]+(e-?[0-9]+)?)?"
}

content_1=$(get_numbers $1)
echo $content_1
content_2=$(get_numbers $2)
echo $content_2

if [ "$content_1" = "$content_2" ]; then
    echo 0
else
    echo 1
fi
