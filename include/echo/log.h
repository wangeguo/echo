#ifndef _ECHO_LOG_H_
#define _ECHO_LOG_H_

// log level
#define LOG_INFO    1
#define LOG_WARRING 2
#define LOG_ERROR   3

#include <string>

void log(int log_level, const std::string &msg);
#endif

