#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include <QColor>

#include "model.h"

struct draw_scene
{
    QGraphicsScene *scene;
    double width;
    double heigth;
    QColor color;
};

using draw_scene_t = struct draw_scene;

error_code scene_clear(const draw_scene_t &draw_scene);

error_code model_draw(draw_scene_t &draw_scene, model_t &model);
error_code lines_draw(draw_scene_t &draw_scene, points_t points, edges_t edges);
error_code line_draw(draw_scene_t &draw_scene, point_t first_point, point_t second_point);

#endif // DRAW_H
