//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_COORDINATECONVERTCREATOR_H
#define LAB_03_COORDINATECONVERTCREATOR_H

#include "Concepts/Concepts.h"
#include "Strategies/CoordinateConvert/BaseCoordinateConvert.h"
#include "Strategies/CoordinateConvert/Default/DefaultCoordinateConvert.h"

#include <memory>

template <typename BaseCoordinateConvert, Derivative<BaseCoordinateConvert> DeriveCoordinateConvert, typename ... Args>
    requires ConstructableWith<DeriveCoordinateConvert, Args ...>
class CoordinateConvertCreator
{
public:
    CoordinateConvertCreator() = default;
    ~CoordinateConvertCreator() = default;

    template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
    static std::shared_ptr<BaseCoordinateConvert> create(CallArgs && ... args);

};

#include "CoordinateConvertCreator.hpp"

using DefaultCoordinateConvertCreator = CoordinateConvertCreator<BaseCoordinateConvert, DefaultCoordinateConver>;

#endif //LAB_03_COORDINATECONVERTCREATOR_H