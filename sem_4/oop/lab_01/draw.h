#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>
#include <QColor>

#include "model.h"

struct draw_scene
{
    QGraphicsScene *scene;
    double width;
    double height;
    QColor color;
};

using draw_scene_t = struct draw_scene;

error_code model_draw(const draw_scene_t &draw_scene, const model_t &model);

#endif // DRAW_H
