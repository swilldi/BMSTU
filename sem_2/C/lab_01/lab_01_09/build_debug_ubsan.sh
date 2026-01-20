#!/bin/bash

clang -c ./*.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=undefined -fno-omit-frame-pointer -g

clang ./*.o -fsanitize=undefined -o app.exe -lm
