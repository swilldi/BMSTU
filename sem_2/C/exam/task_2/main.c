// #include <stdio.h>
// #include "info.h"
// #include "exit_code.h"
// #include "io_func.h"
// #include <string.h>

// void reverse_word(char *str)
// {
//     size_t len = strlen(str);
//     for (size_t i = 0; i < len / 2; i++)
//     {
//         char mem = str[i];
//         str[i] = str[len - 1 - i];
//         str[len - 1 - i] = mem;
//     }
// }

// void reverse_words(char *str)
// {
//     char new_str[STR_LEN];
//     char *word = strtok(str, " \t");
//     while (word != NULL)
//     {
//         reverse_word(word);
//         strcat(new_str, word);
//         word = strtok(NULL, " \t");
//         if (word != NULL)
//         {
//             strcat(new_str, " ");
//         }   
//     }
//     strcpy(str, new_str);
// }

// int main(void)
// {
//     char str[STR_LEN + 1];
//     // ввод строки
//     int rc = input_str(str);
//     if (rc != OK)
//     {
//         return rc;
//     }

//     // переворачивание слов
//     reverse_words(str);

//     printf("'%s'", str);
// }

#include <stdio.h>
// typedef enum { RED, GREEN, BLUE } color_t;

// int main(void)
// {
//     color_t color = RED;
// }

void func(double num, int *a, double *b)
{
	*a = (int)num;
	*b = num - *a;
}

int main(void)
{
	double num = 12.49;
	int a;
	double b;

	func(num, &a, &b); // a = 12, b = 0.49 (наверно, a может быть 0.488...89)
    printf("%d\n%g\n", a, b);
}