gcc *.c -c -Werror -Wall -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla
gcc *.o -o app.exe -lm