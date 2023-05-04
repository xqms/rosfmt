// rosfmt - type-safe ROS_* logging macros
// Author: Max Schwarz <max.schwarz@ais.uni-bonn.de>

#ifndef ROSFMT_H
#define ROSFMT_H

#if __cplusplus < 201103L
#error rosfmt needs C++11 support. Suggestion: add "set(CMAKE_CXX_STANDARD 11)" \
    to your CMakeLists.txt.

#else

// Enable old auto-detection of std::ostream operators
#ifndef ROSFMT_NO_DEPRECATED_OSTREAM
#ifndef FMT_DEPRECATED_OSTREAM
#define FMT_DEPRECATED_OSTREAM
#endif
#endif

#include <ros/console.h>

#include <fmt/core.h>

#include <string>

namespace rosfmt
{

std::string vformat(fmt::string_view format_str, fmt::format_args args);

template<typename ... Args>
std::string format(const std::string& formatString, const Args& ... args)
{
	fmt::format_arg_store<fmt::format_context, Args...> as{args...};
	return rosfmt::vformat(formatString, as);
}

template<typename... Args>
void print(
	ros::console::FilterBase* filter, void* logger, ros::console::Level level,
	const char* file, int line, const char* function,
	fmt::format_string<Args...> fmt, Args&&... args)
{
	std::string s = rosfmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...));
	std::stringstream ss;
	ss << s;
	ros::console::print(filter, logger, level, ss, file, line, function);
}

}

#define ROSFMT_PRINT_AT_LOCATION_WITH_FILTER(filter, ...) \
    ::rosfmt::print(filter, __rosconsole_define_location__loc.logger_, __rosconsole_define_location__loc.level_, __FILE__, __LINE__, __ROSCONSOLE_FUNCTION__, __VA_ARGS__)

#define ROSFMT_PRINT_AT_LOCATION(...) \
    ROSFMT_PRINT_AT_LOCATION_WITH_FILTER(NULL, __VA_ARGS__)

/**
 * \brief Log to a given named logger at a given verbosity level, only if a given condition has been met, with printf-style formatting
 *
 * \note The condition will only be evaluated if this logging statement is enabled
 *
 * \param cond Boolean condition to be evaluated
 * \param level One of the levels specified in ::ros::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "ros.<package_name>".  Use ROSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define ROSFMT_LOG_COND(cond, level, name, ...) \
  do \
  { \
    ROSCONSOLE_DEFINE_LOCATION(cond, level, name); \
    \
    if (ROS_UNLIKELY(__rosconsole_define_location__enabled)) \
    { \
      ROSFMT_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, only the first time it is hit when enabled, with printf-style formatting
 *
 * \param level One of the levels specified in ::ros::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "ros.<package_name>".  Use ROSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define ROSFMT_LOG_ONCE(level, name, ...) \
  do \
  { \
    ROSCONSOLE_DEFINE_LOCATION(true, level, name); \
    static bool hit = false; \
    if (ROS_UNLIKELY(__rosconsole_define_location__enabled) && ROS_UNLIKELY(!hit)) \
    { \
      hit = true; \
      ROSFMT_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, limited to a specific rate of printing, with printf-style formatting
 *
 * \param level One of the levels specified in ::ros::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "ros.<package_name>".  Use ROSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 * \param period The period it should actually trigger at most
 */
#define ROSFMT_LOG_THROTTLE(period, level, name, ...) \
  do \
  { \
    ROSCONSOLE_DEFINE_LOCATION(true, level, name); \
    static double last_hit = 0.0; \
    ::ros::Time now = ::ros::Time::now(); \
    if (ROS_UNLIKELY(__rosconsole_define_location__enabled) && ROS_UNLIKELY(last_hit + period <= now.toSec())) \
    { \
      last_hit = now.toSec(); \
      ROSFMT_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, limited to a specific rate of printing, with printf-style formatting
 *
 * \param level One of the levels specified in ::ros::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "ros.<package_name>".  Use ROSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 * \param period The period it should actually trigger at most
 */
#define ROSFMT_LOG_DELAYED_THROTTLE(period, level, name, ...) \
  do \
  { \
    ROSCONSOLE_DEFINE_LOCATION(true, level, name); \
    ::ros::Time __ros_log_delayed_throttle__now__ = ::ros::Time::now(); \
    static double __ros_log_delayed_throttle__last_hit__ = __ros_log_delayed_throttle__now__.toSec(); \
    if (ROS_UNLIKELY(__rosconsole_define_location__enabled) && ROS_UNLIKELY(__ros_log_delayed_throttle__last_hit__ + period <= __ros_log_delayed_throttle__now__.toSec())) \
    { \
      __ros_log_delayed_throttle__last_hit__ = __ros_log_delayed_throttle__now__.toSec(); \
      ROSFMT_PRINT_AT_LOCATION(__VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, with user-defined filtering, with printf-style formatting
 *
 * \param filter pointer to the filter to be used
 * \param level One of the levels specified in ::ros::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "ros.<package_name>".  Use ROSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define ROSFMT_LOG_FILTER(filter, level, name, ...) \
  do \
  { \
    ROSCONSOLE_DEFINE_LOCATION(true, level, name); \
    if (ROS_UNLIKELY(__rosconsole_define_location__enabled) && (filter)->isEnabled()) \
    { \
      ROSFMT_PRINT_AT_LOCATION_WITH_FILTER(filter, __VA_ARGS__); \
    } \
  } while(false)

/**
 * \brief Log to a given named logger at a given verbosity level, with printf-style formatting
 *
 * \param level One of the levels specified in ::ros::console::levels::Level
 * \param name Name of the logger.  Note that this is the fully qualified name, and does NOT include "ros.<package_name>".  Use ROSCONSOLE_DEFAULT_NAME if you would like to use the default name.
 */
#define ROSFMT_LOG(level, name, ...) ROSFMT_LOG_COND(true, level, name, __VA_ARGS__)

#include "macros_generated.h"

#endif // C++11

#endif // include guard
