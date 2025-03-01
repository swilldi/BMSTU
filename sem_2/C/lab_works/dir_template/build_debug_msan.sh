#!/bin/bash

clang -c main.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=memory -fPIE -fno-omit-frame-pointer -g 

clang main.o -fsanitize=memory -fPIE -pie -o app.exe -lm