/*
 * @file HttpMacros.h
 * @brief http-related macros
 * 
 * @version 1.0
 * @date Sun Sep 16 00:12:26 2012
 * 
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef http_HttpMacros_H_
#define http_HttpMacros_H_

// ex. PUT / HTTP/1.1
#define HTTP_REQUEST_LINE_SEPARATOR_CHR     ' '
#define HTTP_REQUEST_LINE_SEPARATOR_STR     " "

// ex. HTTP/1.1 200 OK
#define HTTP_STATUS_LINE_SEPARATOR_CHR      ' '
#define HTTP_STATUS_LINE_SEPARATOR_STR      " "

// ex. Content-Type:text/html
#define HTTP_NAME_VALUE_SEPARATOR_CHR       ':'
#define HTTP_NAME_VALUE_SEPARATOR_STR       ":"

// ex.
// Content-MD5:2e34fdc57a\r\n
// Content-Type:text/html\r\n
#define HTTP_CR_CHR                            '\r'
#define HTTP_CR_STR                            "\r"
#define HTTP_LF_CHR                            '\n'
#define HTTP_LF_STR                            "\n"
#define HTTP_CRLF                              "\r\n"

// param separator
#define HTTP_PARAM_LEADER_CHR               '?'
#define HTTP_PARAM_LEADER_STR               "?"
#define HTTP_PARAM_SEPARATOR_CHR            '&'
#define HTTP_PARAM_SEPARATOR_STR            "&"
#define HTTP_PARAM_NV_SEPARATOR_CHR         '='
#define HTTP_PARAM_NV_SEPARATOR_STR         "="

// version
#define HTTP_VERSION_11                     "HTTP/1.1"

// header name
#define HTTP_CONTENT_LENGTH         "Content-Length"
#define HTTP_DATE                   "Date"
#define HTTP_AUTHORIZATION          "Authorization"
#define HTTP_HOST                   "Host"
#define HTTP_LAST_MODIFIED          "Last-Modified"
#define HTTP_RANGE                  "Range"


#endif  // http_HttpMacros_H_


