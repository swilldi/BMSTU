//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_BASEEXCEPTION_H
#define LAB_03_BASEEXCEPTION_H

#include <source_location>
#include <exception>

#define MSG_LEN 256
using location = std::source_location;

class BaseException: public std::exception {
public:
    BaseException(const char *info, const location &loc = location::current()) noexcept;
    virtual const char *what() const noexcept override;
protected:
    char msg[MSG_LEN];
};

#endif //LAB_03_BASEEXCEPTION_H