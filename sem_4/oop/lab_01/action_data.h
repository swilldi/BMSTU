#ifndef ACTION_DATA_H
#define ACTION_DATA_H

struct move_data
{
    double x;
    double y;
    double z;
};

struct rotate_data
{
    double x;
    double y;
    double z;
};

struct scale_data
{
    double x;
    double y;
    double z;
};

using move_data_t = struct move_data;
using rotate_data_t = struct rotate_data;
using scale_data_t = struct scale_data;

#endif // ACTION_DATA_H
