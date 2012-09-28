/*
 * @file util.cpp
 * @brief small utils
 *
 * @version 1.0
 * @date Sat Sep 29 00:13:23 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "util/util.h"

#include <ctype.h>

#include <string>

std::string
ossfs::util::ltrim(const std::string &s)
{
    if (s.empty()) {
        return s;
    }

    int idx = 0;

    for (idx = 0; idx < s.length() && isspace(s[idx++]);) {
        // intentionally empty
    }

    return s.substr(--idx);
}

std::string
ossfs::util::rtrim(const std::string &s)
{
    if (s.empty()) {
        return "";
    }

    int idx = 0;

    for (idx = s.length() - 1; idx > 0 && isspace(s[idx--]);) {
        // intentionally empty
    }

    return s.substr(0, idx + 2);
}

std::string
ossfs::util::trim(const std::string &s)
{
    return ltrim(rtrim(s));
}

