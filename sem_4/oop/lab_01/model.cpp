#include "model.h"


model_t model_init()
{
    model_t model;
    edges_init(model.edges);
    points_init(model.points);
    point_default(model.center);
    return model;
}

void model_free(model_t &model)
{
    edges_free(model.edges);
    points_free(model.points);
}


error_code model_read_from_file(FILE *f, model_t &model)
{
    if (!f)
        return INVALID_FILE_ERR;
    
    error_code rc;
    // чтение точек
    rc = points_read_from_file(f, model.points);
    if (rc != OK)
    {
        model_free(model);
        return rc;
    }
    points_center(model.points, model.center);

    // чтение вершин
    rc = edges_read_from_file(f, model.edges);
    if (rc != OK)
    {
        model_free(model);
        return rc;
    }

    return OK;
}
error_code model_write_to_file(FILE *f, const model_t &model)
{
    if (!f)
        return INVALID_FILE_ERR;
    
    error_code rc;
    // запись точек
    rc = points_write_to_file(f, model.points);
    if (rc != OK)
        return rc;

    // запись вершин
    rc = edges_write_to_file(f, model.edges);
    if (rc != OK)
        return rc;

    return OK;
}

error_code model_move(model_t &model, const move_data_t &move)
{
    error_code rc = OK;
    rc = points_move(model.points, move);

    return rc;

}

error_code model_rotate(model_t &model, const rotate_data_t &rotate)
{
    error_code rc = OK;
    rc = points_rotate(model.points, rotate, model.center);

    return rc;
}
error_code model_scale(model_t &model, const scale_data_t &scale)
{
    error_code rc = OK;
    points_scale(model.points, scale, model.center);

    return rc;
}
