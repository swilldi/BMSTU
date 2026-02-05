#ifndef ACTIONS_H
#define ACTIONS_H

#include "error_codes.h"
#include "draw.h"

enum action
{
    DRAW = 0,
    SCALE,
    MOVE,
    ROTATE,
    LOAD,
    SAVE,
    EXIT
};

using action_t = enum action;

struct request
{
    action_t action;
    union 
    {
        const char *file_name;
        move_data_t move;
        rotate_data_t rotate;
        scale_data_t scale;
        draw_scene_t scene;
    };
};

using request_t = struct request;

error_code complete_request(request_t request);


#endif // ACTIONS_H
