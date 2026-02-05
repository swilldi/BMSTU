#include "draw.h"

#include <QGraphicsScene>
#include <QPen>
error_code scene_clear(const draw_scene_t &draw_scene)
{
    if (!draw_scene.scene)
        return (error_code)1;

    QGraphicsScene *scene = draw_scene.scene;
    scene->clear();

    return OK;
}

error_code model_draw(draw_scene_t &draw_scene, model_t &model)
{
    error_code rc;
    // много проверов

    rc = scene_clear(draw_scene);

    rc = lines_draw(draw_scene, model.points, model.edges);
    if (rc != OK)
        return rc;

    return  OK;
}

error_code lines_draw(draw_scene_t &draw_scene, points_t points, edges_t edges)
{
    for (size_t i = 0; i < edges.count; i++)
    {
        edge_t  edge = edges.data[i];
        point_t from_point = points.data[edge.from_index], to_point = points.data[edge.to_index];
        line_draw(draw_scene, from_point, to_point);
    }

    return OK;
}

error_code line_draw(draw_scene_t &draw_scene, point_t first_point, point_t second_point)
{
    // Много проверок
    QGraphicsScene *scene = draw_scene.scene;
    QPen pen;
    pen.setColor(draw_scene.color);
    scene->addLine(first_point.x, first_point.y, second_point.x, second_point.y, pen);

    return OK;

}
