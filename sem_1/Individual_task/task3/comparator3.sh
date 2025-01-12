#!/bin/bash

# удаление буква слева и справа от числа
# echo "ghj123 kd" | sed -e "s/^[^[:digit:].]*//" | sed -e "s/[[:digit:].]*$//"

function extruct_numbers() {
    numbers=""
    for num in $(cat $1); do
      if [[ $num =~ \-[0-9]+(\.[0-9]+)? && ! $num =~ [0-9]+e[\-+]?[0-9]+ ]]; then
        echo $num | sed -E 's/[^0-9]*([0-9]+(\.[0-9]+)?)[^0-9]*/-\1/'
      elif [[ $num =~ [0-9]+(\.[0-9]+)? && ! $num =~ [0-9]+e\[\-+]?[0-9]+ ]]; then
        echo $num | sed -E 's/[^0-9]*([0-9]+(\.[0-9]+)?)[^0-9]*/\1/'
      fi
    done
}


# считываем параметры, если они есть
if [[ "$1" =~ -[a-zA-z] ]]; then
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
numbers_1=$(extruct_numbers $1)
numbers_2=$(extruct_numbers $2)

# вывод последовательностей чисел содержащихся в файлах
if [[ "$parameters" = "-v" ]]; then
  echo $1 contain numbers: $numbers_1
  echo $2 contain numbers: $numbers_2
fi

# проверяем совпадают ли файлы
if [ "$numbers_1" == "$numbers_2" ]; then
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
