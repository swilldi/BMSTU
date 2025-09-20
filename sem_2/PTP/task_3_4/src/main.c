#include <stdio.h>
#define NAME_LEN 7
#define ACHICE_COUNT 5

// struct person
// {
//     char name[NAME_LEN];            // 7  байт + 1 -–> 8
//     int age;                        // 4  байт + 4 --> 8
//     double height;                  // 8  байт + 0 --> 8
//     char literal_group;             // 1  байт + 3 --> 4
//     int any_nums[ACHICE_COUNT];     // 20 байт + 0 --> 16
// };                                  // 40 байт + 8 --> 48

// #pragma pack(push, 1)
// struct person
// {
//     char name[NAME_LEN];            // 7  байт
//     int age;                        // 4  байт
//     double height;                  // 8  байт
//     char literal_group;             // 1  байт
//     int any_nums[ACHICE_COUNT];     // 20 байт
// };
// #pragma pack(pop)

// struct person
// {
//     char name[NAME_LEN];            // 7  байт -–> 7
//     char literal_group;             // 1  байт --> 1
//     int age;                        // 4  байт --> 8
//     int any_nums[ACHICE_COUNT];     // 20 байт --> 16
//     double height;                  // 8  байт --> 8
// };                                  // 40 байт --> 48

// int main(void)
// {
//     struct person p = {
//         .name = "Dima",
//         .age = 18,
//         .height = 180.2,
//         .literal_group = 'B',
//         .any_nums = {5, 41, 7, 20}
//     };

//     printf("My name is %s\nI'm %d old\n", p.name, p.age);
// }


union un
{
    int i;
    double d;
    char c;
};

int main(void)
{
    union un u_1 = { .d = 1.2 };

    u_1.c = 'A';
}