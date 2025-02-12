/*
С клавиатуры задаётся время в секундах. Перевести в часы, минуты, секунды
и вывести на экран.
*/

#include <stdio.h>

int main()
{
    int hours, minutes, seconds;
    printf("Seconds: ");
    scanf("%d", &seconds);

    minutes = seconds / 60;
    hours = minutes / 60;
    seconds %= 60;

    printf("%d:%d:%d\n", hours, minutes, seconds);
    
    return 0;
}
