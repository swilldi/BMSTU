#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum 
{
    BREND,
    COUNTRY,
    SERVIES,
    PRISE,
    COLOR,
    IS_NEW,
    WARRANTY,
    YEAR,
    MILEAGE,
    OWNERS,
    REPAIRING
} car_fields;

// Страны производители
typedef enum 
{
    CHINA,
    FRANCE,
    GERMANY,
    ITALY,
    JAPAN,
    KOREA,
    RUSSIA,
    SWEDEN,
    UK,
    USA
} countries;

#define COMMAND_MAX 9

typedef enum 
{
    EXIT,
    ADD_NEW_FIELD,
    REMOVE_FIELD,
    SEARCH,
    NOT_SORT_TABLE,
    TABLE_KEY,
    TABLE_CAR,
    TABLE_CAR_BY_KEY,
    CMP_TABLE_METHOD,
    CMP_SORT
} command_t;


#endif
