#include <stdio.h>  // нужно в начале поставить # и значение после include поместить в <>, и лишняя буква u
int main()  // не объявлено возврашаемое значени функции и не правильный порядок скобок: сначала () потом {}
{
int s;
s = 56;  // двоеточине не нужно ставить
printf("Year has %d weeks", s);  // print -> printf | Year has s weeks -> "Year has s weeks" | s -> %d | ("...", s) | ;
}