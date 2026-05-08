//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_BASECOMMAND_H
#define LAB_03_BASECOMMAND_H

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
};

#endif //LAB_03_BASECOMMAND_H