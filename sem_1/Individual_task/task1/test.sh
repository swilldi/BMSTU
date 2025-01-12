#!/bin/bash

for directory in $(ls tests | grep test); do
  f_1="tests/$directory/file_1.txt"
  f_2="tests/$directory/file_2.txt"

  ./comparator1.sh $f_1 $f_2

  if [[ "$?" = "$(cat tests/$directory/answer.txt)" ]]; then
    echo $directory: Successfully
  else
    echo $directory: Failed
  fi
  echo

done