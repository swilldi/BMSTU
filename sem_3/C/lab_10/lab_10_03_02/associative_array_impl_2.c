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

struct assoc_array_type
{
    assoc_array_t next;
    int num;
    char *key;
};

/**
 * Создает объект ассоциативный массив.
 *
 * \return Созданный объект или NULL
 */
assoc_array_t assoc_array_create(void)
{
    assoc_array_t head = malloc(sizeof(struct assoc_array_type));
    if (!head)
        return NULL;

    head->key = NULL;
    head->num = 0;
    head->next = NULL;

    return head;
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

    assoc_array_t cur = (*arr)->next;
    assoc_array_t next;

    while (cur)
    {
        next = cur->next;
        // assoc_array_free_contenst(cur->key, NULL, NULL);
        free(cur->key);
        free(cur);
        cur = next;
    }

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

    assoc_array_t cur = arr->next;
    assoc_array_t prev = arr;

    // проверка, что ключ не входит
    while (cur)
    {
        if (strcmp(cur->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;
        prev = cur;
        cur = cur->next;
    }

    // выделение памяти под ноду
    assoc_array_t elem = malloc(sizeof(struct assoc_array_type));
    if (!elem)
        return ASSOC_ARRAY_MEM;

    // заполнение данных
    elem->key = strdup(key);
    if (!elem->key)
    {
        free(elem);
        return ASSOC_ARRAY_MEM;
    }

    elem->num = num;
    elem->next = NULL;

    // Вставка элемента
    prev->next = elem;

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
    if (!arr || !key || !num || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_t cur = arr->next;
    while (cur)
    {
        if (strcmp(cur->key, key) == 0)
        {
            *num = &cur->num;
            return ASSOC_ARRAY_OK;
        }
        cur = cur->next;
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

    assoc_array_t prev = arr;
    assoc_array_t cur = arr->next;

    while (cur)
    {
        if (strcmp(cur->key, key) == 0)
        {
            prev->next = cur->next;
            assoc_array_free_contenst(cur->key, NULL, NULL);
            free(cur);
            return ASSOC_ARRAY_OK;
        }

        prev = cur;
        cur = cur->next;
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

    assoc_array_t cur = arr->next;
    assoc_array_t next;

    while (cur)
    {
        next = cur->next;
        assoc_array_free_contenst(cur->key, NULL, NULL);
        free(cur);
        cur = next;
    }

    arr->next = NULL;
    return ASSOC_ARRAY_OK;
}

/*
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

    assoc_array_t cur = arr->next;
    while (cur)
    {
        action(cur->key, &cur->num, param);
        cur = cur->next;
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

    assoc_array_t cur = arr->next;
    if (!cur)
        return ASSOC_ARRAY_NOT_FOUND;

    assoc_array_t best = cur;

    cur = cur->next;
    while (cur)
    {
        if (strcmp(cur->key, best->key) < 0)
            best = cur;
        cur = cur->next;
    }

    *num = &best->num;
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

    assoc_array_t cur = arr->next;
    if (!cur)
        return ASSOC_ARRAY_NOT_FOUND;

    assoc_array_t best = cur;

    cur = cur->next;
    while (cur)
    {
        if (strcmp(cur->key, best->key) > 0)
            best = cur;
        cur = cur->next;
    }

    *num = &best->num;
    return ASSOC_ARRAY_OK;
}
