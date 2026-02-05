#include <cstdlib>
#include "error_codes.h"
#include "points.h"

error_code points_data_create(point_t* &points, const size_t count)
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
    points.data = NULL;
    points.count = 0;
}

void points_init(points_t &points)
{
    points.count = 0;
    points.data = NULL;
}


static error_code count_points_read_from_file(FILE *f, size_t &count)
{
    if (!f)
        return INVALID_FILE_ERR;

    long long tmp_count;
    if (fscanf(f, "%lld", &tmp_count) != 1)
        return INVALID_FILE_DATA;
    if (tmp_count <= 0)
        return INVALID_DATA_RANGE;

    count = tmp_count;
    return OK;
}

error_code points_read_from_file(FILE *f, points_t &points)
{
    if (!f)
        return INVALID_FILE_ERR;

    // количество точек
    error_code rc = count_points_read_from_file(f, points.count);
    if (rc != OK)
        return rc;

    // выделение памяти под точки
    rc = points_data_create(points.data, points.count);
    if (rc != OK)
        return rc;

    // чтение точек
    for (size_t i = 0; i < points.count; i++)
    {
        rc = point_read_from_file(f, points.data[i]);
        if (rc != OK)
        {
            points_free(points);
            return rc;
        }
    }

    return OK;
}

error_code points_write_to_file(FILE *f, const points_t &points)
{
    error_code rc = OK;
    if (!f)
        return INVALID_FILE_ERR;

    fprintf(f, "%lu\n", points.count);
    for (size_t i = 0; i < points.count; i++)
    {
        rc = point_write_to_file(f, points.data[i]);
        if (rc != OK)
            return rc;
    }

    return rc;
}

error_code points_move(points_t &points, const move_data_t &move)
{
    for (size_t i = 0; i < points.count; i++)
    {
        point_move(points.data[i], move);
    }
    return OK;
}

error_code points_rotate(points_t &points, const rotate_data_t &rotate, const point_t center)
{
    for (size_t i = 0; i < points.count; i++)
    {
        point_rotate(points.data[i], rotate, center);
    }
    return OK;
}

error_code points_scale(points_t &points, const scale_data_t &scale, const point_t center)
{
    for (size_t i = 0; i < points.count; i++)
    {
        point_scale(points.data[i], scale, center);
    }
    return OK;
}


void points_center(points_t &points, point_t &center)
{
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
}



















