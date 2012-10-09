/*
 * @file OssResponse.h
 * @brief OSS response packet.
 *
 * @version 1.0
 * @date Tue Oct  9 14:22:10 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef oss_OssResponse_H_
#define oss_OssResponse_H_


#include "http/HttpResponse.h"


namespace ossfs
{


class OssResponse : public HttpResponse
{
public:
    OssResponse();

    ~OssResponse();
};


}  // namespace ossfs


#endif  // oss_OssResponse_H_

