/*
 * @file OssProxy.h
 * @brief proxy all operations with Aliyun OSS
 *
 * @version 1.0
 * @date Tue Oct  9 09:35:58 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef oss_OssProxy_H_
#define oss_OssProxy_H_

#include <string>
#include <list>
#include <map>


namespace ossfs
{


class OssProxy
{
public:
    OssProxy();

    OssProxy(
        const std::string &host,
        const std::string &id,
        const std::string &key
    );

    ~OssProxy();

    inline void setHost(const std::string &host);

    inline void setAccessId(const std::string &id);

    inline void setAccessKey(const std::string &key);

    /**
     * @brief GetBucket(List Objects)
     *          use it to implement list dir logic
     *
     * @param bucket
     * @param prefix
     * @param delimiter
     * @param objects [out]
     *
     * @return error code
     */
    std::string listObjects(
        const std::string &bucket,
        const std::string &prefix,
        const std::string &delimiter,
        std::list<std::string> *objects
    );

    /**
     * @brief PutObject
     *
     * @param bucket
     * @param object object name
     * @param data data to upload
     * @param headers additional http headers
     *
     * @return
     */
    std::string putObject(
        const std::string &bucket,
        const std::string &object,
        const std::string &data,
        const std::map<std::string, std::string> &headers
    );

    std::string putObject(
        const std::string &bucket,
        const std::string &object,
        const std::string &data
    );

    std::string headObject(
        const std::string &bucket,
        const std::string &object
    );

    std::string deleteObject(
        const std::string &bucket,
        const std::string &object
    );


private:
    std::string _host;
    std::string _accessId;
    std::string _accessKey;
};

void
OssProxy::setHost(const std::string &host)
{
    _host = host;
}

void
OssProxy::setAccessId(const std::string &id)
{
    _accessId = id;
}

void
OssProxy::setAccessKey(const std::string &key)
{
    _accessKey = key;
}


}

#endif  // oss_OssProxy_H_

