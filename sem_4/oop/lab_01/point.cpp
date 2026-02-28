#include "point.h"
#include "error_codes.h"
#include <cmath>


void point_init(point_t &point, const double x, const double y, const double z)
{
    point.x = x;
    point.y = y;
    point.z = z;
}
void point_default(point_t &point)
{
    point.x = point.y = point.z = 0;
}

// чтегие точки из файла
error_code point_read_from_file(point_t &point, FILE* const f)
{
    if (!f)
        return FILE_INVALID;

    error_code rc = OK;
    if (fscanf(f, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        rc = FILE_INVALID_TYPE_DATA;

    return rc;
}

// запись точку в файл
error_code point_write_to_file(FILE* const f, const point_t &point)
{
    if (!f)
        return FILE_INVALID;

    error_code rc = OK;
    fprintf(f, "%lf %lf %lf\n", point.x, point.y, point.z);

    return rc;
}

// === Перемещение точки ===
void point_move(point_t &point, const move_data_t &move)
{
    point.x += move.x;
    point.y += move.y;
    point.z += move.z;
}

static void point_to_origin(point_t &point, const point_t center)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;
}

static void point_from_origin(point_t &point, const point_t center)
{
    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

// === Вращение точки ===
static double to_radian(double angle)
{
    return angle * M_PI / 180;
}

static void apply_rotate(double &a, double &b, double angle_cos, double angle_sin)
{
    double tmp_a = a, tmp_b = b;

    a = tmp_a * angle_cos + tmp_b * angle_sin;
    b = -tmp_a * angle_sin + tmp_b * angle_cos;
}

static void point_rotate_by_x(point_t &point, const double angle)
{
    double angle_cos = cos(to_radian(angle)), angle_sin = sin(to_radian(angle));
    apply_rotate(point.y, point.z, angle_cos, angle_sin);
}

static void point_rotate_by_y(point_t &point, const double angle)
{
    double angle_cos = cos(to_radian(angle)), angle_sin = sin(to_radian(angle));
    apply_rotate(point.x, point.z, angle_cos, angle_sin);
}

static void point_rotate_by_z(point_t &point, const double angle)
{
    double angle_cos = cos(to_radian(angle)), angle_sin = sin(to_radian(angle));
    apply_rotate(point.x, point.y, angle_cos, angle_sin);
}

void point_rotate(point_t &point, const rotate_data_t &rotate, const point_t center)
{
    point_to_origin(point, center);

    point_rotate_by_x(point, rotate.x);
    point_rotate_by_y(point, rotate.y);
    point_rotate_by_z(point, rotate.z);

    point_from_origin(point, center);
}

// === Масштабирование точки ===
static void point_scale(point_t &point, const scale_data_t scale)
{
    point.x *= scale.x;
    point.y *= scale.y;
    point.z *= scale.z;
}

void point_scale(point_t &point, const scale_data_t &scale, const point_t center)
{
    point_to_origin(point, center);
    point_scale(point, scale);
    point_from_origin(point, center);
}






















