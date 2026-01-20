/*
Ассоциативный массив на динамическом списке
*/
#define _GNU_SOURCE
#include "associative_array.h"

/**
 * Тип ассоциативный массив: ключ - строка, значение - целое число.
 *
 * Ключ не может быть пустой строкой.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define START_LEN 10

typedef struct
{
    char *key;
    int num;
} assoc_array_elemet_t;

struct assoc_array_type
{
    assoc_array_elemet_t *data;
    int len;
    int max_len;
};

/**
 * Создает объект ассоциативный массив.
 *
 * \return Созданный объект или NULL
 */
assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (arr)
    {
        assoc_array_elemet_t *data = calloc(START_LEN, sizeof(assoc_array_elemet_t));
        if (data)
        {
            arr->data = data;
            arr->len = 0;
            arr->max_len = START_LEN;
        }
        else
        {
            free(arr);
            arr = NULL;
        }
    }

    return arr;
}

/**
 * Удаляет объект ассоциативный массив.
 *
 * \param[in,out] arr - описатель массив
 *
 * После вызова этой функции переменная, переданная в качестве параметра, имеет
 * значение NULL.
 */
void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || !*arr)
        return;

    assoc_array_each(*arr, assoc_array_free_contenst, NULL);
    free((*arr)->data);
    (*arr)->data = NULL;
    free(*arr);
    *arr = NULL;
}

/**
 * Добавляе пару "ключ-значение" в ассоциативный массив.
 *
 * \param[in,out] arr - описатель массива
 * \param[in] key - ключ
 * \param[in] num - значение
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_MEM, ASSOC_ARRAY_KEY_EXISTS)
 */
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    // проверка наличия ключа
    for (int i = 0; i < arr->len; i++)
    {
        assoc_array_elemet_t *cur = &arr->data[i];
        if (cur->key && strcmp(cur->key, key) == 0)
        {
            return ASSOC_ARRAY_KEY_EXISTS;
        }
    }

    // расширение массива при необходимости
    if (arr->len == arr->max_len)
    {
        assoc_array_elemet_t *tmp_data = realloc(arr->data,
        sizeof(assoc_array_elemet_t) * arr->max_len * 2);
        if (!tmp_data)
            return ASSOC_ARRAY_MEM;

        arr->data = tmp_data;
        arr->max_len *= 2;
    }

    assoc_array_elemet_t *cur = &arr->data[arr->len];
    cur->key = strdup(key);
    cur->num = num;
    arr->len += 1;

    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение по ключу.
 *
 * \param[in] arr - описатель массива
 * \param[in] key - ключ
 * \param[out] num - указатель на значение, соответствующее ключу (в случае успеха)
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND)
 */
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || key[0] == '\0' || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = 0; i < arr->len; i++)
    {
        assoc_array_elemet_t *cur = &arr->data[i];
        if (cur->key && strcmp(cur->key, key) == 0)
        {
            *num = &cur->num;
            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * Удаляет значение по ключу.
 *
 * \param[in,out] arr - описатель массива
 * \param[in] key - ключ
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_MEM, ASSOC_ARRAY_NOT_FOUND)
 */
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = 0; i < arr->len; i++)
    {
        assoc_array_elemet_t *cur = &arr->data[i];
        if (cur->key && strcmp(cur->key, key) == 0)
        {
            assoc_array_free_contenst(cur->key, NULL, NULL);
            for (int j = i; j < arr->len - 1; j++)
            {
                arr->data[j] = arr->data[j + 1];
            }
            arr->data[arr->len - 1].key = NULL;
            arr->data[arr->len - 1].num = 0;
            arr->len -= 1;
            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

void assoc_array_free_contenst(const char *key, int *num, void *param)
{
    (void)num;
    (void)param;
    free((char *)key);
}
/**
 * Очищает ассоциативный массив (т.е. массив становится пустым).
 *
 * \param[in,out] arr - описатель массива
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM)
 */
assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_each(arr, assoc_array_free_contenst, NULL);
    memset(arr->data, 0, sizeof(assoc_array_elemet_t) * arr->max_len);
    arr->len = 0;
    return ASSOC_ARRAY_OK;
}

/**
 * Применяет к значениям указанное действие.
 *
 * \param[in] arr - описатель массива
 * \param[in] action - указатель на функцию обратного вызова для обработки очередного значения
 * \param[in] param - параметр функции обратного вызова (может быть NULL)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM)
 */
assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (int i = 0; i < arr->len; i++)
    {
        assoc_array_elemet_t *cur = &arr->data[i];
        if (cur->key)
            action(cur->key, &cur->num, param);
    }

    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение соответствующее минимальному ключу.
 *
 * \param[in] arr - описатель массива
 * \param[out] num - указатель на значение, соответствующее минимальному ключу (в случае успеха)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND - т.е. массив пустой)
 */

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    else if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    char *min_key = NULL;
    int *min_value = NULL;

    for (int i = 0; i < arr->len; i++)
    {
        assoc_array_elemet_t *cur = &arr->data[i];
        if (cur->key)
        {
            if (!min_key || strcmp(cur->key, min_key) < 0)
            {
                min_key = cur->key;
                min_value = &cur->num;
            }
        }
    }

    if (!min_key)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = min_value;
    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение соответствующее максимальному ключу.
 *
 * \param[in] arr - описатель массива
 * \param[out] num - указатель на значение, соответствующее максимальному ключу (в случае успеха)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND - т.е. массив пустой)
 */
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;
    else if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    char *max_key = NULL;
    int *max_value = NULL;

    for (int i = 0; i < arr->len; i++)
    {
        assoc_array_elemet_t *cur = &arr->data[i];
        if (cur->key)
        {
            if (!max_key || strcmp(cur->key, max_key) > 0)
            {
                max_key = cur->key;
                max_value = &cur->num;
            }
        }
    }

    if (!max_key)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = max_value;
    return ASSOC_ARRAY_OK;
}
