#!/bin/bash

input=$1

result=$(../../app.exe < input)
if [ result == 0 ]; then
    exit 0
else
    exit 1
fi