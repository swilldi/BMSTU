#!/bin/bash

gcc -c main.c -O0 -Wall -g3 -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla

gcc main.o -o app.exe -lm