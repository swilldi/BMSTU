#ifndef STRUCTS_H__
#define STRUCTS_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "enums.h"

#define STR_LEN 32

#define BREND_LEN 9
#define SERVISE_MAX 2
#define COLOR_LEN 8
#define COUNTRIES_MAX USA
#define PRISE_MAX 999999999.99
#define IS_NEW_MAX 2
#define WARRANTY_MAX 100
#define YEAR_MAX 4000
#define MILAGE_MAX 1000000
#define OWNERS_MAX 100
#define REPAIRING_MAX 100

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
    char brend[STR_LEN];        // марка 
    double min_prise; // цена
    double max_prise; // цена
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
