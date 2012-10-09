/*
 * @file OssMacros.h
 * @brief OSS-related macros.
 *
 * @version 1.0
 * @date Tue Oct  9 00:56:14 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef oss_OssMacros_H_
#define oss_OssMacros_H_


#define OSS_HEADER_PREFIX      "x-oss-"

#define OSS_USER_META_HEADER_PREFIX     "x-oss-meta-"

#define OSS_PATH_SEPARATOR_STR      "/"

// sub resources and override query string should be signed

// sub resources
#define OSS_RESOURCE_ACL        "acl"
#define OSS_RESOURCE_GROUP      "group"
#define OSS_RESOURCE_UPLOAD_ID      "uploadId"
#define OSS_RESOURCE_PART_NUMBER    "partNumber"
#define OSS_RESOURCE_UPLOADS        "uploads"

// override query string
#define OSS_OVERRIDE_CONTENT_TYPE       "response-content-type"
#define OSS_OVERRIDE_CONTENT_LANGUAGE   "response-content-language"
#define OSS_OVERRIDE_EXPIRES            "response-expires"
#define OSS_OVERRIDE_CACHE_CONTROL      "response-cache-control"
#define OSS_OVERRIDE_CONTENT_DISPOSITION    "response-content-disposition"
#define OSS_OVERRIDE_CONTENT_ENCODING       "response-content-encoding"

// other params
#define OSS_PARAM_PREFIX        "prefix"
#define OSS_PARAM_DELIMITER     "delimiter"

// oss error code

#define OSS_SUCCESS      "OssSuccess"
#define OSS_FAILED       "OssFailed"



#endif  // oss_OssMacros_H_

