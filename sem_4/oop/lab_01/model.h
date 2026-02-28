#ifndef MODEL_H
#define MODEL_H

#include "points.h"
#include "edges.h"
#include "action_data.h"


struct model
{
    point_t center;
    points_t points;
    edges_t edges;
};

using model_t = struct model;

model_t model_init();
void model_free(model_t &model);

error_code model_is_valid(const model_t &model);

error_code model_read_from_file(model_t &model, FILE* const f);
error_code model_write_to_file(FILE* const f, const model_t &model);

error_code model_move(model_t &model, const move_data_t &move);
error_code model_rotate(model_t &model, const rotate_data_t &rotate);
error_code model_scale(model_t &model, const scale_data_t &scale);


#endif // MODEL_H
