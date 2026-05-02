//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_COORDINATECONVERTCREATOR_HPP
#define LAB_03_COORDINATECONVERTCREATOR_HPP

#include "Concepts/Concepts.h"
#include "Strategies/CoordinateConvert/Creator/CoordinateConvertCreator.h"

template <typename BaseCoordinateConvert, Derivative<BaseCoordinateConvert> DerivedCoordinateConvert, typename ... Args>
    requires ConstructableWith<DerivedCoordinateConvert, Args ...>
template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
std::shared_ptr<BaseCoordinateConvert> CoordinateConvertCreator<
    BaseCoordinateConvert, DerivedCoordinateConvert, Args ...>::create(CallArgs && ... args)
{
    return std::make_shared<DerivedCoordinateConvert>(std::forward<CallArgs>(args)...);
}

#endif //LAB_03_COORDINATECONVERTCREATOR_HPP