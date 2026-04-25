#include "strlen64.h"

long my_strlen64(const char *str)
{
    long len;
    __asm__ volatile (
        "cld\n\t"
        "movq %1, %%rdi\n\t"
        "xorb %%al, %%al\n\t"
        "movq $0xFFFFFFFFFFFFFFFF, %%rcx\n\t"
        "repne scasb\n\t"
        "notq %%rcx\n\t"
        "decq %%rcx\n\t"
        "movq %%rcx, %0\n\t"
        : "=r" (len)
        : "r"  (str)
        : "rax", "rcx", "rdi", "cc", "memory"
    );
    return len;
}
