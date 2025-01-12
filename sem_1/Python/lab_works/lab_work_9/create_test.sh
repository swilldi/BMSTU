#!/bin/zsh

echo -n "Создавать новый тест? [д/н] [y/n]: "
read createTest

echo "Необходимо ввести номер программы или же all, чтобы запустить всё"
echo -n "Введите номер программы: "
read option

if echo "$createTest" | grep -Eq "^[yд]$"; then
  echo "$option" | python3 test.py
fi

if echo "$option" | grep -Eq "^[1-7]$"; then
  echo "Задание номер $option"
  python3 $option.py < test_$option.txt

elif echo "$option" | grep -Eq "^all$"; then
  for i in $(seq 1 7); do
    echo Задание номер $i
    python3 $i.py < test_$i.txt
    done;
fi
