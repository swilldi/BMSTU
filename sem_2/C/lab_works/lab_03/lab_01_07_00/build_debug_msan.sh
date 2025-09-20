#!/bin/bash

clang -c main.c -g3 -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g 

clang main.o -o app.exe -lm