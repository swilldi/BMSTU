#!/bin/bash
pos=$(find ./func_tests/data/ -regex ".*pos.*args.txt" | sort)
neg=$(find ./func_tests/data/ -regex ".*neg.*args.txt" | sort)

echo --- POS_TESTS ---
for test in $pos; do
    IFS=' ' read -ra args < "$test"
    n_test=$(echo "$test" | grep -Eo "[0-9]{1,2}" )
    valgrind --leak-check=full --log-file=res.txt -- ./app.exe  "${args[@]}" < ${test/args/in} > /dev/null
    # valgrind --leak-check=full -- ./app.exe  "${args[@]}" < ${test/args/in} > /dev/null
    if grep -q "All heap blocks were freed -- no leaks are possible" res.txt; then
        echo pos_"$n_test": OK
    else
        echo pos_"$n_test": FAIL
    fi
done

echo --- NEG_TESTS ---
for test in $neg; do
    IFS=' ' read -ra args < "$test"
    n_test=$(echo "$test" | grep -Eo "[0-9]{1,2}" )
    valgrind --leak-check=full --log-file=res.txt ./app.exe "${args[@]}" < ${test/args/in} > /dev/null
    # valgrind --leak-check=full ./app.exe "${args[@]}" < ${test/args/in} > /dev/null
    if grep -q "All heap blocks were freed -- no leaks are possible" res.txt; then
        echo neg_"$n_test": OK
    else
        echo neg_"$n_test": FAIL
    fi
done
