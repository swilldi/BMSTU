//
// Created by Dmitriy Dudurev on 13.04.2026.
//

#ifndef LAB_02_BASEEXCEPTION_H
#define LAB_02_BASEEXCEPTION_H

#include <source_location>
#include <exception>

class BaseException : public std::exception
{
public:
    BaseException(const char *info_msg, const std::source_location &location) noexcept;
    const char *what() const noexcept override;

protected:
    static const size_t msg_size = 512;
    char msg[msg_size];
};

#include "BaseException.hpp"

#endif //LAB_02_BASEEXCEPTION_H
