#!/bin/bash

./../../app.exe < "$1" > result_app.txt
if [ "$?" -ne 0 ]; then
    echo 0
else
    echo 1
fi