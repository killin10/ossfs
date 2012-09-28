/*
 * @file util.h
 * @brief samll utils
 *
 * @version 1.0
 * @date Sat Sep 29 00:03:48 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef util_util_H_
#define util_util_H_

#include <sstream>

namespace ossfs
{


namespace util
{

/**
 * @brief convert from source type to dest type
 *
 * @tparam D dest type
 * @tparam S source type
 * @param s source value
 *
 * @return
 */
template <typename D, typename S>
D conv(const S &s);


/**
 * @brief remove whitespace before the string
 *
 * @param s
 *
 * @return
 */
std::string ltrim(const std::string &s);

/**
 * @brief remove whitespace after the string
 *
 * @param s
 *
 * @return
 */
std::string rtrim(const std::string &s);

/**
 * @brief remove whitespace before and after the string
 *
 * @param s
 *
 * @return
 */
std::string trim(const std::string &s);


}  // namespace util


}  // namespace ossfs


template <typename D, typename S>
D
ossfs::util::conv(const S &s)
{
    std::stringstream ss;

    ss << s;

    D d;
    ss >> d;

    return d;
}


#endif  // util_util_H_


