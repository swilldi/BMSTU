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

// проверка модели на корректность
error_code model_is_valid(const model_t &model)
{
    error_code rc = OK;
    rc = edges_is_valid(model.edges);
    if (rc == OK)
    {
        rc = points_is_valid(model.points);
    }

    return rc;
}


// чтение модели из файла
error_code model_read_from_file(model_t &model, FILE* const f)
{
    if (!f)
        return FILE_INVALID;
    

    error_code rc = OK;
    // чтение точек
    rc = points_read_from_file(model.points, f);
    if (rc == OK)
    {
        // определение центра модели
        points_center(model.points, model.center); // <-- киндер сюрприз: центр модели не хранится в файле, а вычисляется по точкам

        // чтение вершин
        rc = edges_read_from_file(model.edges, f);
        if (rc != OK)
        {
            model_free(model);
        }

    }

    return rc;
}

// запись модели в файл
error_code model_write_to_file(FILE* const f, const model_t &model)
{
    error_code rc = model_is_valid(model);
    if (rc != OK)
        return rc;
    if (!f)
        return FILE_INVALID;

    
    // запись точек
    rc = points_write_to_file(f, model.points);
    if (rc == OK)
    {
        // запись вершин
        rc = edges_write_to_file(f, model.edges);
    }

    return rc;
}

// перемещение модели
error_code model_move(model_t &model, const move_data_t &move)
{
    error_code rc = model_is_valid(model);
    if (rc != OK)
        return rc;

    rc = points_move(model.points, move);
    if (rc == OK)
    {
        rc = points_center(model.points, model.center);
    }
    return rc;
}

// вращение модели
error_code model_rotate(model_t &model, const rotate_data_t &rotate)
{
    error_code rc = model_is_valid(model);
    if (rc != OK)
        return rc;

    rc = points_rotate(model.points, rotate, model.center);
    if (rc == OK)
    {
        rc = points_center(model.points, model.center);
    }
    return rc;
}

// масштабирование модели
error_code model_scale(model_t &model, const scale_data_t &scale)
{
    error_code rc = model_is_valid(model);
    if (rc != OK)
        return rc;

    rc = points_scale(model.points, scale, model.center);
    if (rc == OK)
    {
        rc = points_center(model.points, model.center);
    }
    return rc;
}
