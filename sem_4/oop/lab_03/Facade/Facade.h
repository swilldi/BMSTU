//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_FACADE_H
#define LAB_03_FACADE_H
#include "Commands/BaseCommand.h"

#include <memory>


class Facade {
    Facade() = default;
    ~Facade() = default;

    void execute(const std::shared_ptr<BaseCommand> &command);
};


#endif //LAB_03_FACADE_H