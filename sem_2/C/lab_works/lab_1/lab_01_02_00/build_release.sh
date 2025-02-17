#!/bin/bash

gcc -c main.c -Wall -Werror -Wextra - Wpedantic - std=c99 -Wfloat-equal -Wfloat-conversion -Wvla

gcc main.c -o app.exe -lm