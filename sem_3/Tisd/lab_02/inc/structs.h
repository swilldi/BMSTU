#ifndef STRUCTS_H__
#define STRUCTS_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "enums.h"

#define STR_LEN 32

// Информация о не новом автомобиле
typedef struct
{
    uint16_t year;      // год выпуска
    unsigned int mileage;        // пробег
    uint8_t owners;     // кол-во владельцев
    uint8_t repairing;  // кол-во произведенных ремонтов 
} used_car_info;

// Информация о новом автомобиле
typedef struct
{
    uint8_t warranty;  // гарантия в годах
} new_car_info;

// структура с описанием машины в автомагазине
typedef struct 
{
    char brend[STR_LEN];        // марка 
    countries country;  // страна поизводителя
    bool servies;       // есть ли обслуживание
    double prise; // цена
    char color[STR_LEN];        // цвет
    bool is_new;        // состояние новая или нет
    union 
    {
        used_car_info u;
        new_car_info n;
    } info;             // информация в зависимости от состояния
} car_t;

typedef struct 
{
    char *brend;        // марка 
    countries country;  // страна поизводителя
    bool servies;       // есть ли обслуживание
    double min_prise; // цена
    double max_prise; // цена
    char *color;        // цвет
    bool is_new;        // состояние новая или нет
    union 
    {
        used_car_info u;
        new_car_info n;
    } info;             // информация в зависимости от состояния
} car_filter;

typedef struct 
{
    size_t index;
    union
    {
        char *str;
        bool bool_v;
        double num_f;
        int num_i;
        countries country;
    } value;
    
} key_value_t;

#endif
