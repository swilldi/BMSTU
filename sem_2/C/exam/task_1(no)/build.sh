#!/bin/bash

gcc ./*.c -c -Werror -Wall -Wpedantic -Wvla -std=c99 -Wfloat-equal -Wfloat-conversion

gcc ./*.o -lm -o app.exe
