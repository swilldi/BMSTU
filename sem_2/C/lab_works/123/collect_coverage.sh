#!/bin/bash


./build_gcov.sh

cd func_tests/scripts/
./func_tests.sh
cd ../../

gcov app.exe-main.gcda

if [ "$1" = "-v" ]; then
    cat main.c.gcov
    echo
fi

./clean.sh
