#!/bin/bash

./../../app.exe < $1 > result_app.txt
if [ "$?" -eq 0 ]; then
    echo 0
else
    echo 1
fi