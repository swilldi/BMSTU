//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_QRDRAWFACTORY_H
#define LAB_03_QRDRAWFACTORY_H
#include "Factories/Draw/BaseDrawFactory.h"

#include <QGraphicsScene>


class QtDrawFactory : public BaseDrawFactory
{
public:
    QtDrawFactory() = delete;
    QtDrawFactory(std::shared_ptr<QGraphicsScene> scene);
    virtual ~QtDrawFactory() override = default;

    std::unique_ptr<BaseDrawer> create_drawer() override;

private:
    std::weak_ptr<QGraphicsScene> _scene;
};


#endif //LAB_03_QRDRAWFACTORY_H
