/*
 * @file LoggerFactory.cpp
 * @brief Logger factory, you can get a logger from this object
 *          using logger name.
 *
 * @version 1.0
 * @date Tue Oct  2 11:25:50 2012
 *
 * @copyright Copyright (C) 2012 UESTC
 * @author shiwei<shiwei2012@gmail.com>
 */

#include "LoggerFactory.h"

#include <cstdio>
#include <cstdlib>

#include <string>
#include <utility>

#include "LogLevel.h"
#include "ConsoleAppender.h"

namespace ossfs
{


// logger map
std::map<std::string, Logger *> LoggerFactory::m_LoggerMap;

LoggerFactory::LoggerFactory()
{
    // init ROOT Logger
    Logger *rootLogger = new Logger();
    rootLogger->setName("ROOT");
    rootLogger->setLevel(LOG_TRACE);

    Appender *p_Appender = new ConsoleAppender();

    if (p_Appender->init() != 0) {
        fprintf(stderr, "Error occurred while initializing the ROOT logger. Program exited.\n");
        exit(1);
    }

    rootLogger->addAppender(p_Appender);

    m_LoggerMap.insert(std::pair<std::string, Logger *>("ROOT", rootLogger));
}

LoggerFactory::~LoggerFactory()
{
    // 析构所有Logger
    for (std::map<std::string, Logger *>::iterator it = m_LoggerMap.begin();
         it != m_LoggerMap.end();
         ++it) {
        delete(*it).second;
    }
}

Logger *LoggerFactory::getRootLogger()
{
    return m_LoggerMap["ROOT"];
}

}

