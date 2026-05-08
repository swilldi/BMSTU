#include "strlen32.h"

int my_strlen32(const char *str)
{
    int len;
    __asm__ volatile (
        "cld\n\t"
        "movl %1, %%edi\n\t"
        "xorl %%eax, %%eax\n\t"
        "movl $0xFFFFFFFF, %%ecx\n\t"
        "repne scasb\n\t"
        "notl %%ecx\n\t"
        "decl %%ecx\n\t"
        "movl %%ecx, %0\n\t"
        : "=r" (len)
        : "r"  (str)
        : "eax", "ecx", "edi", "cc", "memory"
    );
    return len;
}
