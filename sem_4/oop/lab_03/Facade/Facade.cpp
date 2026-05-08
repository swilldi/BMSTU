//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "Facade.h"

void Facade::execute(const std::shared_ptr<BaseCommand> &command)
{
    command->execute();
}
