#!/bin/bash

function extract() {
    string=""
    flag=1
    OLD_IFS=$IFS
    IFS="\\"
    for substring in $(cat $1); do
      if [[ "$flag" = "0" ]]; then
        echo "$substring "
      elif [[ "$substring" =~ .*string: ]]; then
        echo "$( echo $substring | sed "s/.*string://" )"
        flag=0
      fi
    done
    IFS=$OLD_IFS
}


# считываем параметры, если они есть
if [[ "$1" =~ -[[:alpha:]] ]]; then
  parameters=$1
  shift
fi


# проверка корректности переданных аргументов
for file in $@; do
  if [[ ! -f $file ]]; then
    if [[ "$parameters" = "-v" ]]; then
      echo $file will not find or is not a file
    fi
    exit 2
  fi
done

# вывод полного содержимого файлов
if [[ "$parameters" = "-v" ]]; then
  echo $1 contain: $(cat $1)
  echo $2 contain: $(cat $2)
fi

# выделяем из файлов только числа
substring_1=$(extract $1)
substring_2=$(extract $2)

# вывод последовательностей чисел содержащихся в файлах
if [[ "$parameters" = "-v" ]]; then
  echo $1 contain substring: $substring_1
  echo $2 contain substring: $substring_2
fi

# проверяем совпадают ли файлы
if [[ "$substring_1" = "$substring_2" ]]; then
  if [[ "$parameters" = "-v" ]]; then
    echo result compare: Matched
  fi
  exit 0
else
  if [[ "$parameters" = "-v" ]]; then
    echo result compare: Different
  fi
  exit 1
fi
