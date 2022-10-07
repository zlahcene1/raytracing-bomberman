/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Errors
*/

#include "Errors.hpp"

Error::IndieError::IndieError(const std::string &comp, const std::string &msg)
: _msg(msg), _comp(comp)
{}

const char *Error::IndieError::what() const noexcept
{
    std::string tmp = "Error: " + _comp + ": " + _msg;

    return tmp.c_str();
}

Error::DropDownErrorSelectedButtonNotFound::DropDownErrorSelectedButtonNotFound(const std::string &comp, const std::string &msg)
: IndieError(comp, msg)
{}