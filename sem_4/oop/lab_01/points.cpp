#include <cstdlib>
#include "error_codes.h"
#include "points.h"


error_code points_data_allocate(point_t* &points, const size_t count)
{
    point_t *tmp_arr = (point_t*)malloc(sizeof(point_t) * count);
    if (!tmp_arr)
        return MEMORY_ERR;

    points = tmp_arr;

    return OK;
}

void points_free(points_t &points)
{
    std::free(points.data);
    points_init(points);
}

void points_init(points_t &points)
{
    points.data = NULL;
    points.count = 0;
}


error_code points_is_valid(points_t points)
{
    if (!points.data)
        return POINTS_INVALID;
    if (points.count <= 0)
        return POINTS_EMPTY;

    return OK;
}

// чтение количества точек в файле
static error_code count_points_read_from_file(size_t &count, FILE* const f)
{
    if (!f)
        return FILE_INVALID;


    error_code rc = OK;
    long tmp_count;
    if (fscanf(f, "%ld", &tmp_count) == 1)
    {
        if (tmp_count <= 0)
            rc = FILE_DATA_INVALID_RANGE;
        else
            count = tmp_count;
    }
    else
    {
        rc = FILE_INVALID_TYPE_DATA;
    }

    return rc;
}

// чтение координато точек из файла
error_code points_data_read_from_file(FILE* const f, points_t &points)
{
    if (!f)
        return FILE_INVALID;
    if (points.count <= 0)
        return POINTS_EMPTY;

    error_code rc = OK;
    for (size_t i = 0; i < points.count; i++)
    {
        rc = point_read_from_file(points.data[i], f);
        if (rc != OK)
            break;
    }
    return rc;
}

// чтение точек из файла
error_code points_read_from_file(FILE* const f, points_t &points)
{
    if (!f)
        return FILE_INVALID;

    // количество точек
    error_code rc = count_points_read_from_file(points.count, f);
    if (rc == OK)
    {
        // выделение памяти под точки
        rc = points_data_allocate(points.data, points.count);
        if (rc == OK)
        {
            // чтение точек
            rc = points_data_read_from_file(f, points);
            if (rc != OK)
                points_free(points);
        }
    }

    return rc;
}

// запись точек в файл
error_code points_write_to_file(FILE* const f, const points_t &points)
{
    error_code rc = OK;
    rc = points_is_valid(points);
    if (rc != OK)
        return rc;
    if (!f)
        return FILE_INVALID;

    fprintf(f, "%lu\n", points.count);
    for (size_t i = 0; i < points.count; i++)
    {
        rc = point_write_to_file(f, points.data[i]);
        if (rc != OK)
            return rc;
    }

    return rc;
}

// перемещение точек
error_code points_move(points_t &points, const move_data_t &move)
{
    error_code rc = points_is_valid(points);
    if (rc != OK)
        return rc;


    for (size_t i = 0; i < points.count; i++)
        point_move(points.data[i], move);

    return rc;
}

// вращение точек
error_code points_rotate(points_t &points, const rotate_data_t &rotate, const point_t center)
{
    error_code rc = points_is_valid(points);
    if (rc != OK)
        return rc;

    for (size_t i = 0; i < points.count; i++)
        point_rotate(points.data[i], rotate, center);

    return rc;
}

// масштабирование точек
error_code points_scale(points_t &points, const scale_data_t &scale, const point_t center)
{
    error_code rc = points_is_valid(points);
    if (rc != OK)
        return rc;

    for (size_t i = 0; i < points.count; i++)
        point_scale(points.data[i], scale, center);

    return rc;
}


// подсчет центра точек
error_code points_center(points_t &points, point_t &center)
{
    error_code rc = points_is_valid(points);
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



















