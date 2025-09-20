gcc -c *.c -Wpedantic -Werror -Wall -Wfloat-equal -Wfloat-conversion -std=c99
gcc *.o -o app.exe -lm