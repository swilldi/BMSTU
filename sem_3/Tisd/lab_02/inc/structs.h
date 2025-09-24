#ifndef STRUCTS_H__
#define STRUCTS_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Страны производители
typedef enum 
{
    JAPAN,
    GERMANY,
    USA,
    KOREA,
    FRANCE,
    ITALY,
    UK,
    SWEDEN,
    CHINA,
    RUSSIA
} countries;

// Информация о не новом автомобиле
typedef struct
{
    uint16_t year;      // год выпуска
    int mileage;        // пробег
    uint8_t owners;     // кол-во владельцев
    uint8_t repairing;  // кол-во произведенных ремонтов 
} used_car_info;

// Информация о новом автомобиле
typedef struct
{
    uint16_t warranty;  // гарантия в годах
} new_car_info;

// структура с описанием машины в автомагазине
typedef struct 
{
    char *brend;        // марка 
    countries country;  // страна поизводителя
    bool servies;       // есть ли обслуживание
    unsigned int prise; // цена
    char *color;        // цвет
    bool is_new;        // состояние новая или нет
    union 
    {
        used_car_info u;
        new_car_info n;
    } info;             // информация в зависимости от состояния
} car;

#endif
