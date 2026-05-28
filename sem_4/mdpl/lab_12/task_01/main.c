#include <stdio.h>

size_t strlenAsm(char *str) {
    size_t len = 0;
    asm volatile(
        "mov x0, %[str]\n"
        "mov %[len], #0\n"
        "ldrb w1, [x0, %[len]]\n"
    "1:\n"
        "cbz w1, 2f\n"
        "add %[len], %[len], #1\n"
        "ldrb w1, [x0, %[len]]\n"
        "b 1b\n"
    "2:"
        : [len] "+r" (len) 
        : [str] "r" (str)
        : "cc", "memory", "x0", "x1"
    );

    return len;
}

size_t strlenC(char *str) {
    size_t len = 0;
    while (str[len] != '\0')
        ++len;
    return len;
}

int main(void) {
    printf("Hello world!!!(11): Asm[%lu], C[%lu]\n", strlenAsm("Hello world"), strlenC("Hello world"));
    printf("<Empty>(0): Asm[%lu], C[%lu]\n", strlenAsm(""), strlenC(""));
    printf("a(1): Asm[%lu], C[%lu]\n", strlenAsm("a"), strlenC("a"));
}
