#!/bin/bash

for directory in $(ls tests | grep test_); do
  f_1="tests/$directory/file_1.txt"
  f_2="tests/$directory/file_2.txt"

  ./comparator3.sh -v $f_1 $f_2

  if [[ "$?" = "$(cat tests/$directory/answer.txt)" ]]; then
    echo $directory: Successfully
  else
    echo $directory: Failed
    echo file_1.txt: $(cat $f_1)
    echo file_2.txt: $(cat $f_2)
  fi
  echo

done