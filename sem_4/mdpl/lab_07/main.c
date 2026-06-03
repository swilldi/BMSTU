#include <stdio.h>
#include <string.h>
#include <stddef.h>

extern void my_strcpy(char *dst, const char *src, size_t len);

static size_t my_strlen(const char *s)
{
    size_t len;
#ifdef __x86_64__
    __asm__ volatile (
        ".intel_syntax noprefix\n"
        "mov rdi, %1\n"
        "xor eax, eax\n"
        "mov rcx, -1\n"
        "cld\n"
        "repne scasb\n"
        "not rcx\n"
        "dec rcx\n"
        "mov %0, rcx\n"
        ".att_syntax prefix\n"
        : "=r" (len)
        : "r" (s)
        : "rax", "rcx", "rdi", "cc"
    );
#else
    __asm__ volatile (
        ".intel_syntax noprefix\n"
        "mov edi, %1\n"
        "xor eax, eax\n"
        "mov ecx, -1\n"
        "cld\n"
        "repne scasb\n"
        "not ecx\n"
        "dec ecx\n"
        "mov %0, ecx\n"
        ".att_syntax prefix\n"
        : "=r" (len)
        : "r" (s)
        : "eax", "ecx", "edi", "cc"
    );
#endif
    return len;
}

static void show(const char *label, const char *buf, size_t n)
{
    printf("  %s = \"", label);
    for (size_t i = 0; i < n; i++) {
        unsigned char c = (unsigned char)buf[i];
        if (c >= 0x20 && c < 0x7F) putchar(c);
        else printf("\\x%02X", c);
    }
    printf("\"\n");
}

static void test_strlen(const char *s)
{
    size_t a = my_strlen(s);
    size_t b = strlen(s);
    printf("my_strlen(\"%s\") = %zu  (libc: %zu)  %s\n",
           s, a, b, a == b ? "OK" : "FAIL");
}

static void test_copy_no_overlap(void)
{
    const char *src = "Hello, assembler!";
    char dst[64] = {0};
    size_t n = my_strlen(src) + 1;
    my_strcpy(dst, src, n);
    printf("copy (no overlap): \"%s\"  %s\n",
           dst, strcmp(dst, src) == 0 ? "OK" : "FAIL");
}

static void test_copy_forward_overlap(void)
{
    /* dst < src, перекрытие: сдвиг строки влево на 2 байта */
    char buf[16] = "ABCDEFGHIJ";
    my_strcpy(buf + 0, buf + 2, 8);     /* "CDEFGHIJ" -> в начало */
    /* ожидаем: C D E F G H I J I J */
    const char expected[] = {'C','D','E','F','G','H','I','J','I','J','\0'};
    int ok = (memcmp(buf, expected, 10) == 0);
    printf("copy (dst<src, overlap): "); show("buf", buf, 10);
    printf("  %s\n", ok ? "OK" : "FAIL");
}

static void test_copy_backward_overlap(void)
{
    /* dst > src, перекрытие: сдвиг строки вправо на 2 байта */
    char buf[16] = "ABCDEFGHIJ";
    my_strcpy(buf + 2, buf + 0, 8);     /* "ABCDEFGH" -> со сдвигом */
    /* ожидаем: A B A B C D E F G H */
    const char expected[] = {'A','B','A','B','C','D','E','F','G','H','\0'};
    int ok = (memcmp(buf, expected, 10) == 0);
    printf("copy (dst>src, overlap): "); show("buf", buf, 10);
    printf("  %s\n", ok ? "OK" : "FAIL");
}

int main(void)
{
#ifdef __x86_64__
    printf("=== 64-bit build ===\n");
#else
    printf("=== 32-bit build ===\n");
#endif

    test_strlen("");
    test_strlen("a");
    test_strlen("Hello, world!");
    test_strlen("0123456789abcdef");

    test_copy_no_overlap();
    test_copy_forward_overlap();
    test_copy_backward_overlap();

    return 0;
}
