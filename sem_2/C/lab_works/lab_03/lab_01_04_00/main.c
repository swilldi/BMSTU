/*
Ввод:
amount_cents – количество копеек

Одна бутылка стоит 45 рублей. Её можно сдать и получить 20 рублей

Вывод:
количество бутылок, которые можно купить
*/

#include <stdio.h>

int main(void)
{
    int amount_cents;
    int bottel_prise = 45, bottel_cashback = 20;
    int can_buy_bottels;

    printf("Enter amout of cents: ");
    scanf("%d", &amount_cents);

    can_buy_bottels = (amount_cents - bottel_prise) / (bottel_prise - bottel_cashback) + 1;
    
    printf("Bottels: %d \n", can_buy_bottels);
    return 0;
}
