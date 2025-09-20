#!/bin/zsh

# Компиляция с флагами для M1 и отладки
clang -c ./main.c -g -arch arm64 -Wall -Werror -Wextra -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -o main.o
clang ./main.o -o app -lm

# Очистка временных файлов
# rm -f ./*.o

echo "Сборка завершена. Бинарник: src/app"