#!/bin/bash

./func_tests/scripts/func_tests.sh -q

gcov ./*.gcda

if [ "$1" = "-v" ]; then
    cat ./*.c.gcov
    echo
fi
