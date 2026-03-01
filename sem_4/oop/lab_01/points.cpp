#include <cstdlib>
#include "error_codes.h"
#include "points.h"

// Выделение памяти для массива точек
error_code points_data_allocate(point_t* &points, const size_t count)
{
    point_t *tmp_arr = (point_t*)malloc(sizeof(point_t) * count);
    if (!tmp_arr)
        return MEMORY_ERR;

    points = tmp_arr;

    return OK;
}

// Освобождение памяти из под массива точек
void points_free(points_t &points)
{
    if (points.data)
        free(points.data);

    points_init(points);
}

// Инициализавция структуры с массивом точек
void points_init(points_t &points)
{
    points.data = NULL;
    points.count = 0;
}

error_code points_check(const points_t &points)
{
    error_code rc = OK;
    if (!points.data)
        rc = POINTS_INVALID;
    else if (points.count <= 0)
        rc = POINTS_EMPTY;
    
    return rc;
}

// Чтение количества точек в файле
static error_code count_points_read_from_file(size_t &count, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;

    long tmp_count;
    if (fscanf(f, "%ld", &tmp_count) != 1)
    {
        rc = FILE_INVALID_TYPE_DATA;
    }
    else if (tmp_count <= 0)
    {    
        rc = FILE_DATA_INVALID_RANGE;
    }
    else
    {
        count = tmp_count;
    }

    return rc;
}

// Чтение координат точек из файла
error_code points_data_read_from_file(points_t &points, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;
    if (points.count <= 0)
        return POINTS_EMPTY;

    rc = points_data_allocate(points.data, points.count);
    for (size_t i = 0; rc == OK && i < points.count; i++)
    {
        rc = point_read_from_file(points.data[i], f);
        if (rc != OK)
            points_free(points);
    }
    return rc;
}

// Чтение точек из файла
error_code points_read_from_file(points_t &points, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;

    // количество точек
    rc = count_points_read_from_file(points.count, f);
    if (rc == OK)
    {
        // чтение точек
        rc = points_data_read_from_file(points, f);
    }

    return rc;
}

// Запись точек в файл
error_code points_write_to_file(FILE* const f, const points_t &points)
{
    error_code rc = points_check(points);
    if (rc != OK)
        return rc;
    if (!f)
        return FILE_INVALID;

    fprintf(f, "%lu\n", points.count);
    for (size_t i = 0; rc == OK && i < points.count; i++)
    {
        rc = point_write_to_file(f, points.data[i]);
    }

    return rc;
}

// Перемещение точек
error_code points_move(points_t &points, const move_data_t &move)
{
    error_code rc = points_check(points);
    if (rc != OK)
        return rc;

    for (size_t i = 0; i < points.count; i++)
        point_move(points.data[i], move);

    return rc;
}

// Вращение точек
error_code points_rotate(points_t &points, const rotate_data_t &rotate, const point_t center)
{
    error_code rc = points_check(points);
    if (rc != OK)
        return rc;

    for (size_t i = 0; i < points.count; i++)
        point_rotate(points.data[i], rotate, center);

    return rc;
}

// Масштабирование точек
error_code points_scale(points_t &points, const scale_data_t &scale, const point_t center)
{
    error_code rc = points_check(points);
    if (rc != OK)
        return rc;

    for (size_t i = 0; i < points.count; i++)
        point_scale(points.data[i], scale, center);

    return rc;
}


// Подсчет центра точек
error_code points_center(point_t &center, points_t &points)
{
    error_code rc = points_check(points);
    if (rc != OK)
        return rc;

    point_default(center);
    for (size_t i = 0; i < points.count; i++)
    {
        point_t p = points.data[i];

        center.x += p.x;
        center.y += p.y;
        center.z += p.z;
    }

    center.x /= points.count;
    center.y /= points.count;
    center.z /= points.count;

    return rc;
}



















