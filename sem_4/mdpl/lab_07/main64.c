#include <stdio.h>
#include <string.h>
#include "strlen64.h"

extern void my_strcopy64(char *dst, const char *src, long len);

int main(void)
{
    const char *src = "Hello, Assembly!";
    char dst[32] = {0};
    char buf[16] = "ABCDE";

    long len = my_strlen64(src);
    printf("strlen: %ld (ref: %zu)\n", len, strlen(src));

    my_strcopy64(dst, src, len);
    printf("strcpy: \"%s\", match: %s\n", dst, strcmp(src, dst) == 0 ? "yes" : "no");

    /* перекрытие вправо */
    my_strcopy64(buf + 2, buf, my_strlen64(buf));
    printf("overlap right: \"%s\" (expect \"ABABCDE\")\n", buf);

    return 0;
}
