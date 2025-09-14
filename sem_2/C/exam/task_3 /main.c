#include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// #define WORD_LEN 17
// #define STR_LEN 257
// #define SEPARATORS " .,:;"

// void reverse(char word[])
// {
//     size_t len = strlen(word);
//     printf("%lu\n", len);
//     for (size_t i = 0; i < len / 2; i++)
//     {
//         char mem = word[i];
//         word[i] = word[len - 1 - i];
//         word[len - 1 - i] = mem;
//     }
// }

// int is_num(char word[])
// {
//     for (size_t i = 0; word[i] != '\0'; i++)
//     {
//         if (!(isdigit(word[i])))
//         {
//             return 0;
//         }
//     }
//     return 1;
// }

// void transform(char words[][WORD_LEN], size_t n)
// {
//     for (size_t i = 0; i < n; i++)
//     {
//         // printf("\n%s ", words[i]);
//         if (is_num(words[i]))
//         {
//             // printf("is num");
//             reverse(words[i]);
//         }
//         printf("\n");
//     }
// }

// void print(char arr[][WORD_LEN], size_t n)
// {
//     for (size_t i = 0; i < n; i++)
//     {
//         printf("%s ", arr[i]);
//     }
// }

// int main(void)
// {
//     char str[STR_LEN + 1];
//     if (fgets(str, STR_LEN + 1, stdin) == NULL)
//     {
//         return 1;
//     }
//     if (strlen(str) >= STR_LEN)
//     {
//         return 1;
//     }

//     char words[16][WORD_LEN];
//     char *word;
//     size_t c = 0; 
//     word = strtok(str, SEPARATORS);
//     while (word != NULL)
//     {
//         strcpy(words[c], word);
//         c++;
//         word = strtok(NULL, SEPARATORS);
//     }
//     *strchr(words[c - 1], '\n') = '\0';
//     printf("- %s -", words[c - 1]);
//     transform(words, c);
//     print(words, c);
// }

int main(void)
{
    int a[][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("%d\n", sizeof(a) / sizeof(a[0][0]));
    printf("%d\n", sizeof(a) / sizeof(a[0]));
    printf("%d\n", sizeof(a[0]) / sizeof(a[0][0]));
}
