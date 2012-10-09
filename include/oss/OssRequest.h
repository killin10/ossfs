/*
 * @file OssRequest.h
 * @brief OSS request.
 *
 * @version 1.0
 * @date Tue Oct  9 00:43:18 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef oss_OssRequest_H_
#define oss_OssRequest_H_


#include "http/HttpRequest.h"


#include <set>
#include <string>

namespace ossfs
{


class OssRequest : public HttpRequest
{
public:
    OssRequest();

    ~OssRequest();

    /**
     * @brief sign this request according to OSS spec.
     *
     * @param id  Access Id
     * @param key Access Key
     *
     * @return
     */
    bool sign(const std::string &id, const std::string &key);

private:
    // resources should be signed
    static std::set<std::string> _signResources;
};


}  // namespace ossfs


#endif  // oss_OssRequest_H_


