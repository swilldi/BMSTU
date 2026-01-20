#!/bin/bash

clang -c ./*.c -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -fsanitize=address -fno-omit-frame-pointer -g

clang ./*.o -fsanitize=address -o app.exe -lm
