//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_CONCEPTS_H
#define LAB_03_CONCEPTS_H

#include <concepts>

template <typename T>
concept ConvertibleToDouble = std::convertible_to<T, double>;

#endif //LAB_03_CONCEPTS_H