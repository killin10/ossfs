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
     * @return
     */
    bool sign();
};


}  // namespace ossfs


#endif  // oss_OssRequest_H_


