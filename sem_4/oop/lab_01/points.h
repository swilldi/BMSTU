#ifndef POINTS_H
#define POINTS_H

#include "point.h"

struct points
{
    struct point *data;
    size_t count;
};

using points_t = struct points;

error_code points_data_create(point_t *&points, const size_t count);
void points_init(points_t &points);
void points_free(points_t &points);

error_code points_is_valid(points_t points);

error_code points_read_from_file(FILE* const f, points_t &points);
error_code points_write_to_file(FILE* const f, const points_t &points);

error_code points_move(points_t &points, const move_data_t &move);
error_code points_rotate(points_t &points, const rotate_data_t &rotate, const point_t center);
error_code points_scale(points_t &points, const scale_data_t &scale, const point_t center);

error_code points_center(points_t &points, point_t &point);


#endif // POINTS_H
