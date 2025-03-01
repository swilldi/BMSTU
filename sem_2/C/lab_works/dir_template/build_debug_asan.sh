#!/bin/bash

clang -c main.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=address -fno-omit-frame-pointer -g

clang main.o -fsanitize=address -o app.exe -lm
