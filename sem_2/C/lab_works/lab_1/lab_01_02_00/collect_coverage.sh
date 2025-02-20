#!/bin/bash


gcc -c main.c -g3 -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla 
gcc main.c -o app.exe -lm -coverage

cd func_tests/scripts/
./func_tests.sh
cd ../../

gcov app.exe-main.gcda

./clean.sh
