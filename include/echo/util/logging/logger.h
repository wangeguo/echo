#ifndef _ECHO_UTIL_LOGGING_LOGGER_H_
#define _ECHO_UTIL_LOGGING_LOGGER_H_

#include <string>
#include <echo/util/logging/level.h>

namespace echo {
  namespace util {
	namespace logging {

	  class Logger {

	  public:
		Logger(){}
		void severe(std::string msg);
		void log(echo::util::logging::Level level, std::string msg);
	  };
	} // namespace logging
  } // namespace util
} // namespace echo

#endif // _ECHO_UTIL_LOGGING_LOGGER_H
