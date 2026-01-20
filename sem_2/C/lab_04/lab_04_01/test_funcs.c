#include "string_funcs.h"
#include <string.h>

int test_strpbrk(void)
{
    int res = 0; // макс: 9

    char str_1[] = "0123456789abcdef";
    char str_2[] = "aaabbb1nn1nnn1nnn1";

    // символы внутри строки (т.е. не начало и не конец)
    res += my_strpbrk(str_1, "a") == strpbrk(str_1, "a");
    // символ в начале строки
    res += my_strpbrk(str_1, "0") == strpbrk(str_1, "0");
    // символ в конце строки
    res += my_strpbrk(str_1, "d") == strpbrk(str_1, "d");
    // символа нет
    res += my_strpbrk(str_1, "zxc") == strpbrk(str_1, "zxc");
    // несколько символов в строке, не подряд
    res += my_strpbrk(str_2, "1") == strpbrk(str_2, "1");
    // несколько символов в строке, подряд
    res += my_strpbrk(str_2, "b") == strpbrk(str_2, "b");
    // несколько символов в строке
    res += my_strpbrk(str_2, "ab") == strpbrk(str_2, "ab");
    // несколько символов в строке
    res += my_strpbrk(str_2, "ba") == strpbrk(str_2, "ba");
    // регист в строке и в символах разный
    res += my_strpbrk(str_2, "AB") == strpbrk(str_2, "AB");

    // путсые строки во всех вариациях 
    char empty_str[] = "";
    res += my_strpbrk(empty_str, "AB") == strpbrk(empty_str, "AB");
    res += my_strpbrk("AB", empty_str) == strpbrk("AB", empty_str);
    res += my_strpbrk(empty_str, empty_str) == strpbrk(empty_str, empty_str);
    return res;
}

int test_strspn(void)
{
    int res = 0; // макс: 4

    char str_1[] = "1232uuupuabccca";
    // начало строки
    res += my_strspn(str_1, "123") == strspn(str_1, "123");
    // конец строки
    res += my_strspn(str_1, "abc") == strspn(str_1, "abc");
    // середина строки
    res += my_strspn(str_1, "up") == strspn(str_1, "up");
    // нет символов
    res += my_strspn(str_1, "www") == strspn(str_1, "www");

    char str_2[] = "okoloANNnnnNapom";
    // разный регист
    res += my_strspn(str_2, "an") == strspn(str_2, "an");

    // путсые строки во всех вариациях 
    char empty_str[] = "";
    res += my_strspn(empty_str, "AB") == strspn(empty_str, "AB");
    res += my_strspn("AB", empty_str) == strspn("AB", empty_str);
    res += my_strspn(empty_str, empty_str) == strspn(empty_str, empty_str);

    return res;
}

int test_strcspn(void)
{
    int res = 0; // макс: 4

    char str_1[] = "1232uuupuabccca";
    // начало строки
    res += my_strcspn(str_1, "123") == strcspn(str_1, "123");
    // конец строки
    res += my_strcspn(str_1, "abc") == strcspn(str_1, "abc");
    // середина строки
    res += my_strcspn(str_1, "up") == strcspn(str_1, "up");
    
    char str_3[] = "abcccba";
    // все символы из строки
    res += my_strcspn(str_3, "abs") == strcspn(str_3, "abc");

    char str_2[] = "okoloANNnnnNapom";
    // разный регист
    res += my_strcspn(str_2, "an") == strcspn(str_2, "an");

    // путсые строки во всех вариациях 
    char empty_str[] = "";
    res += my_strcspn(empty_str, "AB") == strcspn(empty_str, "AB");
    res += my_strcspn("AB", empty_str) == strcspn("AB", empty_str);
    res += my_strcspn(empty_str, empty_str) == strcspn(empty_str, empty_str);

    return res;
}

int test_strchr(void)
{
    int res = 0; // макс: 8

    // разный регист буквы в слове и в функции
    char str_1[] = "Hello";
    res += my_strchr(str_1, 'E') == strchr(str_1, 'E');

    // Нет буквы в слове
    res += my_strchr(str_1, 'v') == strchr(str_1, 'v');
    // несколько букв в слове
    res += my_strchr(str_1, 'l') == strchr(str_1, 'l');
    // в строке буква в разных регистрах
    char str_2[] = "Hello how Are you";
    res += my_strchr(str_2, 'a') == strchr(str_2, 'a');
    res += my_strchr(str_2, 'A') == strchr(str_2, 'A');

    // первая буква
    res += my_strchr(str_1, 'H') == strchr(str_1, 'H');

    // последняя буква
    res += my_strchr(str_1, 'o') == strchr(str_1, 'o');
    // буква в случайном месте
    res += my_strchr(str_1, 'w') == strchr(str_1, 'w');

    // путсые строки во всех вариациях 
    char empty_str[] = "";
    res += my_strrchr(empty_str, 'A') == strrchr(empty_str, 'A');
    res += my_strrchr("AB", '\0') == strrchr("AB", '\0');
    res += my_strrchr(empty_str, '\0') == strrchr(empty_str, '\0');

    return res;
}

int test_strrchr(void)
{
    int res = 0; // макс: 8

    // разный регист буквы в слове и в функции
    char str_1[] = "Hello";
    res += my_strrchr(str_1, 'E') == strrchr(str_1, 'E');

    // Нет буквы в слове
    res += my_strrchr(str_1, 'v') == strrchr(str_1, 'v');
    // несколько букв в слове
    res += my_strrchr(str_1, 'l') == strrchr(str_1, 'l');
    // в строке буква в разных регистрах
    char str_2[] = "Hello how Are you";
    res += my_strrchr(str_2, 'a') == strrchr(str_2, 'a');
    res += my_strrchr(str_2, 'A') == strrchr(str_2, 'A');

    // первая буква
    res += my_strrchr(str_1, 'H') == strrchr(str_1, 'H');

    // последняя буква
    res += my_strrchr(str_1, 'o') == strrchr(str_1, 'o');
    // буква в случайном месте
    res += my_strrchr(str_1, 'w') == strrchr(str_1, 'w');

    // путсые строки во всех вариациях 
    char empty_str[] = "";
    res += my_strrchr(empty_str, 'A') == strrchr(empty_str, 'A');
    res += my_strrchr("AB", '\0') == strrchr("AB", '\0');
    res += my_strrchr(empty_str, '\0') == strrchr(empty_str, '\0');

    return res;
}
