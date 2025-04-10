#!/bin/bash

gcc -c *.c -g -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla

gcc *.o -o app.exe -lm