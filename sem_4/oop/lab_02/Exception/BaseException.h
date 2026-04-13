//
// Created by Dmitriy Dudurev on 13.04.2026.
//

#ifndef LAB_02_BASEEXCEPTION_H
#define LAB_02_BASEEXCEPTION_H

#define EXCEPTION_MSG_LEN 512

#include <source_location>
#include <exception>

class BaseException : public std::exception
{
public:
    BaseException(const char *info_msg, const std::source_location &location) noexcept;
    virtual const char *what() const noexcept override;

protected:
    char msg[EXCEPTION_MSG_LEN];
};

#include "BaseException.hpp"

#endif //LAB_02_BASEEXCEPTION_H
