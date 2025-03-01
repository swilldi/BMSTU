#!/bin/bash

gcc -c main.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -coverage

gcc main.o -o app.exe -lm -coverage
