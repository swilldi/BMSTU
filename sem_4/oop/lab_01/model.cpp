#include "model.h"

// инициализация модели
model_t model_init()
{
    model_t model;
    edges_init(model.edges);
    points_init(model.points);
    point_default(model.center);
    return model;
}

// освобождение памяти выделенной для модели
void model_free(model_t &model)
{
    edges_free(model.edges);
    points_free(model.points);
}

error_code model_check(const model_t &model)
{
    error_code rc = points_check(model.points);
    if (rc == OK)
        rc = edges_check(model.edges);
    
    return rc;
}

// загрузка модели
error_code model_load(model_t &model, const char *file_name)
{
    error_code rc = OK;
    if (!file_name)
        return FILE_NAME_INVALID;
    
    FILE *f = fopen(file_name, "r");
    if (!f)
    {
        rc = FILE_OPEN_ERR;
    }
    else
    {
        model_t tmp_model = model_init();
        rc = model_read_from_file(tmp_model, f);
        if (rc == OK)
        {
            rc = points_center(tmp_model.center, tmp_model.points);
            if (rc != OK)
            {
                model_free(tmp_model);
            }
            else
            {
                model_free(model);
                model = tmp_model;
            }
        }

        fclose(f);
    }

    return rc;
}

// сохранение модели
error_code model_save(const char *file_name, const model_t &model)
{
    error_code rc = model_check(model);
    if (rc != OK)
        return rc;
    if (!file_name)
        return FILE_NAME_INVALID;
    
    FILE *f = fopen(file_name, "w");
    if (!f)
    {
        rc = FILE_OPEN_ERR;
    }
    else
    {
        rc = model_write_to_file(f, model);
        fclose(f);
    }

    return rc;
}

// чтение модели из файла
error_code model_read_from_file(model_t &model, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;

    // чтение точек
    rc = points_read_from_file(model.points, f);
    if (rc == OK)
    {
        // чтение ребер
        rc = edges_read_from_file(model.edges, f);
        if (rc != OK)
            points_free(model.points);
    }

    return rc;
}

// запись модели в файл
error_code model_write_to_file(FILE* const f, const model_t &model)
{
    error_code rc = model_check(model);
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
    error_code rc = model_check(model);
    if (rc != OK)
        return rc;

    rc = points_move(model.points, move);
    if (rc == OK)
    {
        rc = points_center(model.center, model.points);
    }

    return rc;
}

// вращение модели
error_code model_rotate(model_t &model, const rotate_data_t &rotate)
{
    error_code rc = model_check(model);
    if (rc != OK)
        return rc;

    rc = points_rotate(model.points, rotate, model.center);
    if (rc == OK)
    {
        rc = points_center(model.center, model.points);
    }

    return rc;
}

// масштабирование модели
error_code model_scale(model_t &model, const scale_data_t &scale)
{
    error_code rc = model_check(model);
    if (rc != OK)
        return rc;

    rc = points_scale(model.points, scale, model.center);
    if (rc == OK)
    {
        rc = points_center(model.center, model.points);
    }

    return rc;
}
