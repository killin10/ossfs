/*
 * @file HttpResponse.h
 * @brief http response packet
 *
 * @version 1.0
 * @date Sat Sep 15 16:49:44 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef HTTP_HTTPRESPONSE_H_
#define HTTP_HTTPRESPONSE_H_

#include <string>
#include <map>


namespace ossfs
{


class HttpResponse
{
public:
    HttpResponse();

    virtual ~HttpResponse();

    bool parseFromString(const std::string &data);

    bool serializeToString(std::string *pData) const;

protected:
    std::string _version;
    std::string _statusCode;
    std::string _reasonPhrase;

    std::map<std::string, std::string> _headers;

    std::string _body;
};


}



#endif  // HTTP_HTTPRESPONSE_H_

