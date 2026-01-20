#!/bin/bash

#!/bin/bash

res_file="result.txt"

IFS=' ' read -ra args < "$3"
# echo "$1"
n=$(echo "$1" | grep -Eo "[0-9][0-9]")
in_file=func_tests/data/pos_"$n"_in_file.txt
out_file=func_tests/data/pos_"$n"_out_file.txt
work_file="work_file.bin"

# echo "$in_file" "$work_file"
./app.exe import "$in_file" "$work_file"

if [ "${args[0]}" = "p" ]; then
    if ./app.exe "${args[@]}" < "$1" > "$res_file" && ./func_tests/scripts/comparator.sh ./"$res_file" "$2" ; then
        exit 0
    else
        exit 1
    fi
elif [ "${args[0]}" = "s" ]; then
    ./app.exe "${args[@]}"
    ./app.exe export "$work_file" "$res_file"
    
    if ./func_tests/scripts/comparator.sh ./"$res_file" "$out_file"; then
        exit 0
    else
        exit 1
    fi
fi
