#ifndef POINT_H
#define POINT_H

#include <cstdio>
#include "error_codes.h"
#include "action_data.h"

struct point
{
    double x;
    double y;
    double z;
};

using point_t = struct point;

void point_init(point_t &point, const double x, const double y, const double z);
void point_default(point_t &point);

error_code point_read_from_file(point_t &point, FILE* const f);
error_code point_write_to_file(FILE* const f, const point_t &point);

void point_move(point_t &point, const move_data_t &move);
void point_rotate(point_t &point, const rotate_data_t &rotate, const point_t center);
void point_scale(point_t &point, const scale_data_t &scale, const point_t center);

#endif // POINT_H
