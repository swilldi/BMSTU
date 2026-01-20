#!/bin/bash

gcc -c ./*.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla
# gcc -c main.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla

gcc ./*.o -o app.exe -lm
