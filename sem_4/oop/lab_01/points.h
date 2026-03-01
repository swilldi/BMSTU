#ifndef POINTS_H
#define POINTS_H

#include "point.h"

struct points
{
    struct point *data;
    size_t count;
};

using points_t = struct points;

error_code points_data_allocate(point_t *&points, const size_t count);
void points_init(points_t &points);
void points_free(points_t &points);

error_code points_check(const points_t &points);

error_code points_read_from_file(points_t &points, FILE* const f);
error_code points_write_to_file(FILE* const f, const points_t &points);

error_code points_move(points_t &points, const move_data_t &move);
error_code points_rotate(points_t &points, const rotate_data_t &rotate, const point_t center);
error_code points_scale(points_t &points, const scale_data_t &scale, const point_t center);

error_code points_center(point_t &center, points_t &points);


#endif // POINTS_H
