#include <QGraphicsScene>
#include <QPen>

#include "draw.h"


static error_code scene_clear(const draw_scene_t &draw_scene);
static error_code lines_draw(const draw_scene_t &draw_scene, const points_t &points, const edges_t &edges);

// отрисовка модели
error_code model_draw(const draw_scene_t &draw_scene, const model_t &model)
{
    // проверки draw_scene
    if (!draw_scene.scene)
        return DRAW_SCENE_SCENE_INVALID;
    if (draw_scene.height == 0)
        return DRAW_SCENE_HEIGHT_INVALID_RANGE;
    if (draw_scene.width == 0)
        return DRAW_SCENE_WIDTH_INVALID_RANGE;
    
    error_code rc = OK;

    rc = scene_clear(draw_scene);
    if (rc == OK)
    {
        rc = lines_draw(draw_scene, model.points, model.edges);
    }

    return rc;
}


// очистка сцены
error_code scene_clear(const draw_scene_t &draw_scene)
{
    if (!draw_scene.scene)
        return DRAW_SCENE_SCENE_INVALID;

    QGraphicsScene *scene = draw_scene.scene;
    scene->clear();

    return OK;
}

// установка точки относительно центра scene
static error_code point_to_center_scene(const draw_scene_t &draw_scene, point_t &point)
{
    if (draw_scene.height == 0)
        return DRAW_SCENE_HEIGHT_INVALID_RANGE;
    if (draw_scene.width == 0)
        return DRAW_SCENE_WIDTH_INVALID_RANGE;

    point.x += draw_scene.width / 2;
    point.y += draw_scene.height / 2;

    return OK;
}

// Отрисовка линии по двум точкам
static error_code line_draw(const draw_scene_t &draw_scene, const point_t &first_point, const point_t &second_point)
{
    if (!draw_scene.scene)
        return DRAW_SCENE_SCENE_INVALID;

    QGraphicsScene *scene = draw_scene.scene;
    QPen pen = QPen(draw_scene.color);
    scene->addLine(first_point.x, first_point.y, second_point.x, second_point.y, pen);

    return OK;
}

// Отрисочка линий по точкам и ребрам
static error_code lines_draw(const draw_scene_t &draw_scene, const points_t &points, const edges_t &edges)
{
    error_code rc = OK;
    for (size_t i = 0; i < edges.count; i++)
    {
        edge_t  edge = edges.data[i];
        point_t from_point = points.data[edge.from_index], to_point = points.data[edge.to_index];

        rc = point_to_center_scene(draw_scene, from_point);
        if (rc != OK)
            break;

        rc = point_to_center_scene(draw_scene, to_point);
        if (rc != OK)
            break;

        rc = line_draw(draw_scene, from_point, to_point);
        if (rc != OK)
            break;
    }

    return rc;
}
