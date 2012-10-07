/*
 * @file log.h
 * @brief Log-related headers.
 *
 * @version 1.0
 * @date Tue Oct  2 11:18:44 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#ifndef log_log_H_
#define log_log_H_

#include <string.h>
#include <errno.h>

#include "LogLevel.h"
#include "Logger.h"
#include "LoggerFactory.h"

// 使用__VA_ARGS__必须要有可变参数
//#define DEV_LOG(logger, _fmt_, ...)  \
//  logger->debug(__FILE__, __LINE__, __FUNCTION__, _fmt_, __VA_ARGS__)

#define TRACE_LOG(_fmt_, args...)  \
    LoggerFactory::getInstance()->getRootLogger()->trace(  \
            __FILE__, __LINE__, __FUNCTION__, _fmt_, ##args)

#define DEBUG_LOG(_fmt_, args...)  \
    LoggerFactory::getInstance()->getRootLogger()->debug(  \
            __FILE__, __LINE__, __FUNCTION__, _fmt_, ##args)

#define INFO_LOG(_fmt_, args...)   \
    LoggerFactory::getInstance()->getRootLogger()->info(  \
            _fmt_, ##args)

#define WARN_LOG(_fmt_, args...)   \
    LoggerFactory::getInstance()->getRootLogger()->warn(  \
            _fmt_, ##args)

#define ERROR_LOG(_fmt_, args...)   \
    LoggerFactory::getInstance()->getRootLogger()->error(  \
            _fmt_, ##args)

#define FATAL_LOG(_fmt_, args...)   \
    LoggerFactory::getInstance()->getRootLogger()->fatal(  \
            _fmt_, ##args)

#endif // log_log_H_

