#!/bin/bash

function get_numbers
{
    grep -Eo "[-]?[1-9][0-9]*(\.[0-9]*[1-9]+(e-?[0-9]+)?)?" "$1"
}

content_1=$(get_numbers "$1")
# echo "$content_1"
content_2=$(get_numbers "$2")
# echo "$content_2"

if [ "$content_1" = "$content_2" ]; then
    exit 0
else
    exit 1
fi
