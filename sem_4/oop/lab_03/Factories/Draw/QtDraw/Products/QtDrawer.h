//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_QTDRAWER_H
#define LAB_03_QTDRAWER_H
#include "Factories/Draw/Products/BaseDrawer.h"
#include <QGraphicsScene>


class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
    QtDrawer(std::shared_ptr<QGraphicsScene> scene);

    virtual ~QtDrawer() override = default;

    void draw_line(const Point &a, const Point &b) override;
    void draw_line(double x1, double y1, double x2, double y2) override;

    void clear() override;

    size_t get_height() const noexcept override;
    size_t get_width() const noexcept override;

private:
    std::shared_ptr<QGraphicsScene> _scene;
};


#endif //LAB_03_QTDRAWER_H
