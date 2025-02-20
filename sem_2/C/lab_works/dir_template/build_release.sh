#!/bin/bash

gcc -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -o app.exe -lm main.c 
