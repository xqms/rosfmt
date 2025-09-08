// rosfmt - type-safe ROS_* logging macros
// Author: Max Schwarz <max.schwarz@ais.uni-bonn.de>

#ifndef ROSFMT_H
#define ROSFMT_H

#include <rclcpp/logging.hpp>
#include <rcutils/logging_macros.h>

#include <fmt/core.h>

#include <string>

namespace rosfmt {

std::string vformat(fmt::string_view format_str, fmt::format_args args);

template <typename... Args>
std::string format(const std::string &formatString, const Args &...args) {
  fmt::format_arg_store<fmt::format_context, Args...> as{args...};
  return rosfmt::vformat(formatString, as);
}

} // namespace rosfmt

#define ROSFMT_STATIC_ASSERT_LOGGER(logger)                                    \
  do {                                                                         \
    static_assert(                                                             \
        ::std::is_convertible_v<decltype(logger), ::rclcpp::Logger>,           \
        "First argument to logging macros must be an rclcpp::Logger");         \
  } while (0)

// Only available in rclutils >= 7.0.0
#ifdef RCLCPP_LOG_NAMED

/**
 * \def ROSFMT_LOG
 * Log a message with given severity.
 * \param logger The `rclcpp::Logger` to use
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG(severity, logger, ...)                                      \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_NAMED(severity, (logger).get_name(), "%s",                     \
                      rosfmt::format(__VA_ARGS__).c_str());                    \
  } while (0)

/**
 * \def ROSFMT_LOG_ONCE
 * Log a message with given severity with the following condition:
 * - All log calls except the first one are ignored.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_ONCE(severity, logger, ...)                                 \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_COND_ONCE_NAMED(severity, (logger).get_name(), "%s",           \
                                rosfmt::format(__VA_ARGS__).c_str());          \
  } while (0)

/**
 * \def ROSFMT_LOG_EXPRESSION
 * Log a message with given severity with the following condition:
 * - Log calls are ignored when the expression evaluates to false.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param expression The expression determining if the message should be logged
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_EXPRESSION(severity, logger, expression, ...)               \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_EXPRESSION_NAMED(severity, expression, (logger).get_name(),    \
                                 "%s", rosfmt::format(__VA_ARGS__).c_str());   \
  } while (0)

/**
 * \def ROSFMT_LOG_FUNCTION
 * Log a message with given severity with the following condition:
 * - Log calls are ignored when the function returns false.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param function The functions return value determines if the message should
 * be logged
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_FUNCTION(severity, logger, function, ...)                   \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_FUNCTION_NAMED(severity, function, (logger).get_name(), "%s",  \
                               rosfmt::format(__VA_ARGS__).c_str());           \
  } while (0)

/**
 * \def ROSFMT_LOG_SKIPFIRST
 * Log a message with given severity with the following condition:
 * - The first log call is ignored but all subsequent calls are processed.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_SKIPFIRST(severity, logger, ...)                            \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_SKIPFIRST_NAMED(severity, (logger).get_name(), "%s",           \
                                rosfmt::format(__VA_ARGS__).c_str());          \
  } while (0)

/**
 * \def ROSFMT_LOG_THROTTLE
 * Log a message with given severity with the following condition:
 * - Log calls are ignored if the last logged message is not longer ago than the
 * specified duration.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param clock rclcpp::Clock that will be used to get the time point.
 * \param duration The duration of the throttle interval as an integral value in
 * milliseconds.
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_THROTTLE(severity, logger, clock, duration, ...)            \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_THROTTLE_NAMED(severity, RCLCPP_LOG_TIME_POINT_FUNC(clock),    \
                               duration, (logger).get_name(), "%s",            \
                               rosfmt::format(__VA_ARGS__).c_str());           \
  } while (0)

/**
 * \def ROSFMT_LOG_SKIPFIRST_THROTTLE
 * Log a message with given severity with the following conditions:
 * - The first log call is ignored but all subsequent calls are processed.
 * - Log calls are ignored if the last logged message is not longer ago than the
 * specified duration.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param clock rclcpp::Clock that will be used to get the time point.
 * \param duration The duration of the throttle interval as an integral value in
 * milliseconds.
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_SKIPFIRST_THROTTLE(severity, logger, clock, duration, ...)  \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_SKIPFIRST_THROTTLE_NAMED(                                      \
        severity, RCLCPP_LOG_TIME_POINT_FUNC(clock), duration,                 \
        (logger).get_name(), "%s", rosfmt::format(__VA_ARGS__).c_str());       \
  } while (0)

#else

/**
 * \def ROSFMT_LOG
 * Log a message with given severity.
 * \param logger The `rclcpp::Logger` to use
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG(severity, logger, ...)                                      \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_COND_NAMED(severity, RCUTILS_LOG_CONDITION_EMPTY,              \
                           RCUTILS_LOG_CONDITION_EMPTY, (logger).get_name(),   \
                           "%s", rosfmt::format(__VA_ARGS__).c_str());         \
  } while (0)

/**
 * \def ROSFMT_LOG_ONCE
 * Log a message with given severity with the following condition:
 * - All log calls except the first one are ignored.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_ONCE(severity, logger, ...)                                 \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_COND_NAMED(severity, RCUTILS_LOG_CONDITION_ONCE_BEFORE,        \
                           RCUTILS_LOG_CONDITION_ONCE_AFTER,                   \
                           (logger).get_name(), "%s",                          \
                           rosfmt::format(__VA_ARGS__).c_str());               \
  } while (0)

/**
 * \def ROSFMT_LOG_EXPRESSION
 * Log a message with given severity with the following condition:
 * - Log calls are ignored when the expression evaluates to false.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param expression The expression determining if the message should be logged
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_EXPRESSION(severity, logger, expression, ...)               \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_COND_NAMED(                                                    \
        severity, RCUTILS_LOG_CONDITION_EXPRESSION_BEFORE(expression),         \
        RCUTILS_LOG_CONDITION_EXPRESSION_AFTER, (logger).get_name(), "%s",     \
        rosfmt::format(__VA_ARGS__).c_str());                                  \
  } while (0)

/**
 * \def ROSFMT_LOG_FUNCTION
 * Log a message with given severity with the following condition:
 * - Log calls are ignored when the function returns false.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param function The functions return value determines if the message should
 * be logged
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_FUNCTION(severity, logger, function, ...)                   \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_COND_NAMED(                                                    \
        severity, RCUTILS_LOG_CONDITION_FUNCTION_BEFORE(function),             \
        RCUTILS_LOG_CONDITION_FUNCTION_AFTER, (logger).get_name(), "%s",       \
        rosfmt::format(__VA_ARGS__).c_str());                                  \
  } while (0)

/**
 * \def ROSFMT_LOG_SKIPFIRST
 * Log a message with given severity with the following condition:
 * - The first log call is ignored but all subsequent calls are processed.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_SKIPFIRST(severity, logger, ...)                            \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    RCUTILS_LOG_COND_NAMED(severity, RCUTILS_LOG_CONDITION_SKIPFIRST_BEFORE,   \
                           RCUTILS_LOG_CONDITION_SKIPFIRST_AFTER,              \
                           (logger).get_name(), "%s",                          \
                           rosfmt::format(__VA_ARGS__).c_str());               \
  } while (0)

/**
 * \def ROSFMT_LOG_THROTTLE
 * Log a message with given severity with the following condition:
 * - Log calls are ignored if the last logged message is not longer ago than the
 * specified duration.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param clock rclcpp::Clock that will be used to get the time point.
 * \param duration The duration of the throttle interval as an integral value in
 * milliseconds.
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_THROTTLE(severity, logger, clock, duration, ...)            \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    auto get_time_point =                                                      \
        [&c =                                                                  \
             clock](rcutils_time_point_value_t *time_point) -> rcutils_ret_t { \
      try {                                                                    \
        *time_point = c.now().nanoseconds();                                   \
      } catch (...) {                                                          \
        RCUTILS_SAFE_FWRITE_TO_STDERR(                                         \
            "[rclcpp|logging.hpp] RCLCPP_DEBUG_THROTTLE could not get "        \
            "current time stamp\n");                                           \
        return RCUTILS_RET_ERROR;                                              \
      }                                                                        \
      return RCUTILS_RET_OK;                                                   \
    };                                                                         \
    RCUTILS_LOG_COND_NAMED(                                                    \
        severity,                                                              \
        RCUTILS_LOG_CONDITION_THROTTLE_BEFORE(get_time_point, duration),       \
        RCUTILS_LOG_CONDITION_THROTTLE_AFTER, (logger).get_name(), "%s",       \
        rosfmt::format(__VA_ARGS__).c_str());                                  \
  } while (0)

/**
 * \def ROSFMT_LOG_SKIPFIRST_THROTTLE
 * Log a message with given severity with the following conditions:
 * - The first log call is ignored but all subsequent calls are processed.
 * - Log calls are ignored if the last logged message is not longer ago than the
 * specified duration.
 *
 * \param logger The `rclcpp::Logger` to use
 * \param clock rclcpp::Clock that will be used to get the time point.
 * \param duration The duration of the throttle interval as an integral value in
 * milliseconds.
 * \param ... The format string, followed by the variable arguments for the
 * format string.
 */
#define ROSFMT_LOG_SKIPFIRST_THROTTLE(severity, logger, clock, duration, ...)  \
  do {                                                                         \
    ROSFMT_STATIC_ASSERT_LOGGER(logger);                                       \
    auto get_time_point =                                                      \
        [&c =                                                                  \
             clock](rcutils_time_point_value_t *time_point) -> rcutils_ret_t { \
      try {                                                                    \
        *time_point = c.now().nanoseconds();                                   \
      } catch (...) {                                                          \
        RCUTILS_SAFE_FWRITE_TO_STDERR(                                         \
            "[rclcpp|logging.hpp] RCLCPP_DEBUG_THROTTLE could not get "        \
            "current time stamp\n");                                           \
        return RCUTILS_RET_ERROR;                                              \
      }                                                                        \
      return RCUTILS_RET_OK;                                                   \
    };                                                                         \
    RCUTILS_LOG_COND_NAMED(                                                    \
        severity,                                                              \
        RCUTILS_LOG_CONDITION_THROTTLE_BEFORE(get_time_point, duration)        \
            RCUTILS_LOG_CONDITION_SKIPFIRST_BEFORE,                            \
        RCUTILS_LOG_CONDITION_THROTTLE_AFTER                                   \
            RCUTILS_LOG_CONDITION_SKIPFIRST_AFTER,                             \
        (logger).get_name(), "%s", rosfmt::format(__VA_ARGS__).c_str());       \
  } while (0)

#endif

/** @name Logging macros for severity DEBUG.
 */
#if (RCLCPP_LOG_MIN_SEVERITY > RCLCPP_LOG_MIN_SEVERITY_DEBUG)
// empty logging macros for severity DEBUG when being disabled at compile time
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_SKIPFIRST_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_DEBUG_STREAM_SKIPFIRST_THROTTLE(...)

#else
/**
 * \def ROSFMT_DEBUG
 * \copydoc RCLCPP_LOG
 */
#define ROSFMT_DEBUG(logger, ...)                                              \
  ROSFMT_LOG(RCUTILS_LOG_SEVERITY_DEBUG, logger, __VA_ARGS__)

/**
 * \def ROSFMT_DEBUG_ONCE
 * \copydoc RCLCPP_LOG_ONCE
 */
#define ROSFMT_DEBUG_ONCE(logger, ...)                                         \
  ROSFMT_LOG_ONCE(RCUTILS_LOG_SEVERITY_DEBUG, logger, __VA_ARGS__)

/**
 * \def ROSFMT_DEBUG_EXPRESSION
 * \copydoc RCLCPP_LOG_EXPRESSION
 */
#define ROSFMT_DEBUG_EXPRESSION(logger, expression, ...)                       \
  ROSFMT_LOG_EXPRESSION(RCUTILS_LOG_SEVERITY_DEBUG, logger, expression,        \
                        __VA_ARGS__)

/**
 * \def ROSFMT_DEBUG_FUNCTION
 * \copydoc RCLCPP_LOG_FUNCTION
 */
#define ROSFMT_DEBUG_FUNCTION(logger, function, ...)                           \
  ROSFMT_LOG_FUNCTION(RCUTILS_LOG_SEVERITY_DEBUG, logger, function, __VA_ARGS__)

/**
 * \def ROSFMT_DEBUG_SKIPFIRST
 * \copydoc RCLCPP_LOG_SKIPFIRST
 */
#define ROSFMT_DEBUG_SKIPFIRST(logger, ...)                                    \
  ROSFMT_LOG_SKIPFIRST(RCUTILS_LOG_SEVERITY_DEBUG, logger, __VA_ARGS__)

/**
 * \def ROSFMT_DEBUG_THROTTLE
 * \copydoc RCLCPP_LOG_THROTTLE
 */
#define ROSFMT_DEBUG_THROTTLE(logger, clock, duration, ...)                    \
  ROSFMT_LOG_THROTTLE(RCUTILS_LOG_SEVERITY_DEBUG, logger, clock, duration,     \
                      __VA_ARGS__)

/**
 * \def ROSFMT_DEBUG_SKIPFIRST_THROTTLE
 * \copydoc RCLCPP_LOG_SKIPFIRST_THROTTLE
 */
#define ROSFMT_DEBUG_SKIPFIRST_THROTTLE(logger, clock, duration, ...)          \
  ROSFMT_LOG_SKIPFIRST_THROTTLE(RCUTILS_LOG_SEVERITY_DEBUG, logger, clock,     \
                                duration, __VA_ARGS__)

#endif

/** @name Logging macros for severity INFO.
 */
#if (RCLCPP_LOG_MIN_SEVERITY > RCLCPP_LOG_MIN_SEVERITY_INFO)
// empty logging macros for severity INFO when being disabled at compile time
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_SKIPFIRST_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_INFO_STREAM_SKIPFIRST_THROTTLE(...)

#else
/**
 * \def ROSFMT_INFO
 * \copydoc RCLCPP_LOG
 */
#define ROSFMT_INFO(logger, ...)                                               \
  ROSFMT_LOG(RCUTILS_LOG_SEVERITY_INFO, logger, __VA_ARGS__)

/**
 * \def ROSFMT_INFO_ONCE
 * \copydoc RCLCPP_LOG_ONCE
 */
#define ROSFMT_INFO_ONCE(logger, ...)                                          \
  ROSFMT_LOG_ONCE(RCUTILS_LOG_SEVERITY_INFO, logger, __VA_ARGS__)

/**
 * \def ROSFMT_INFO_EXPRESSION
 * \copydoc RCLCPP_LOG_EXPRESSION
 */
#define ROSFMT_INFO_EXPRESSION(logger, expression, ...)                        \
  ROSFMT_LOG_EXPRESSION(RCUTILS_LOG_SEVERITY_INFO, logger, expression,         \
                        __VA_ARGS__)

/**
 * \def ROSFMT_INFO_FUNCTION
 * \copydoc RCLCPP_LOG_FUNCTION
 */
#define ROSFMT_INFO_FUNCTION(logger, function, ...)                            \
  ROSFMT_LOG_FUNCTION(RCUTILS_LOG_SEVERITY_INFO, logger, function, __VA_ARGS__)

/**
 * \def ROSFMT_INFO_SKIPFIRST
 * \copydoc RCLCPP_LOG_SKIPFIRST
 */
#define ROSFMT_INFO_SKIPFIRST(logger, ...)                                     \
  ROSFMT_LOG_SKIPFIRST(RCUTILS_LOG_SEVERITY_INFO, logger, __VA_ARGS__)

/**
 * \def ROSFMT_INFO_THROTTLE
 * \copydoc RCLCPP_LOG_THROTTLE
 */
#define ROSFMT_INFO_THROTTLE(logger, clock, duration, ...)                     \
  ROSFMT_LOG_THROTTLE(RCUTILS_LOG_SEVERITY_INFO, logger, clock, duration,      \
                      __VA_ARGS__)

/**
 * \def ROSFMT_INFO_SKIPFIRST_THROTTLE
 * \copydoc RCLCPP_LOG_SKIPFIRST_THROTTLE
 */
#define ROSFMT_INFO_SKIPFIRST_THROTTLE(logger, clock, duration, ...)           \
  ROSFMT_LOG_SKIPFIRST_THROTTLE(RCUTILS_LOG_SEVERITY_INFO, logger, clock,      \
                                duration, __VA_ARGS__)

#endif

/** @name Logging macros for severity WARN.
 */
#if (RCLCPP_LOG_MIN_SEVERITY > RCLCPP_LOG_MIN_SEVERITY_WARN)
// empty logging macros for severity WARN when being disabled at compile time
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_SKIPFIRST_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_WARN_STREAM_SKIPFIRST_THROTTLE(...)

#else
/**
 * \def ROSFMT_WARN
 * \copydoc RCLCPP_LOG
 */
#define ROSFMT_WARN(logger, ...)                                               \
  ROSFMT_LOG(RCUTILS_LOG_SEVERITY_WARN, logger, __VA_ARGS__)

/**
 * \def ROSFMT_WARN_ONCE
 * \copydoc RCLCPP_LOG_ONCE
 */
#define ROSFMT_WARN_ONCE(logger, ...)                                          \
  ROSFMT_LOG_ONCE(RCUTILS_LOG_SEVERITY_WARN, logger, __VA_ARGS__)

/**
 * \def ROSFMT_WARN_EXPRESSION
 * \copydoc RCLCPP_LOG_EXPRESSION
 */
#define ROSFMT_WARN_EXPRESSION(logger, expression, ...)                        \
  ROSFMT_LOG_EXPRESSION(RCUTILS_LOG_SEVERITY_WARN, logger, expression,         \
                        __VA_ARGS__)

/**
 * \def ROSFMT_WARN_FUNCTION
 * \copydoc RCLCPP_LOG_FUNCTION
 */
#define ROSFMT_WARN_FUNCTION(logger, function, ...)                            \
  ROSFMT_LOG_FUNCTION(RCUTILS_LOG_SEVERITY_WARN, logger, function, __VA_ARGS__)

/**
 * \def ROSFMT_WARN_SKIPFIRST
 * \copydoc RCLCPP_LOG_SKIPFIRST
 */
#define ROSFMT_WARN_SKIPFIRST(logger, ...)                                     \
  ROSFMT_LOG_SKIPFIRST(RCUTILS_LOG_SEVERITY_WARN, logger, __VA_ARGS__)

/**
 * \def ROSFMT_WARN_THROTTLE
 * \copydoc RCLCPP_LOG_THROTTLE
 */
#define ROSFMT_WARN_THROTTLE(logger, clock, duration, ...)                     \
  ROSFMT_LOG_THROTTLE(RCUTILS_LOG_SEVERITY_WARN, logger, clock, duration,      \
                      __VA_ARGS__)

/**
 * \def ROSFMT_WARN_SKIPFIRST_THROTTLE
 * \copydoc RCLCPP_LOG_SKIPFIRST_THROTTLE
 */
#define ROSFMT_WARN_SKIPFIRST_THROTTLE(logger, clock, duration, ...)           \
  ROSFMT_LOG_SKIPFIRST_THROTTLE(RCUTILS_LOG_SEVERITY_WARN, logger, clock,      \
                                duration, __VA_ARGS__)

#endif

/** @name Logging macros for severity ERROR.
 */
#if (RCLCPP_LOG_MIN_SEVERITY > RCLCPP_LOG_MIN_SEVERITY_ERROR)
// empty logging macros for severity ERROR when being disabled at compile time
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_SKIPFIRST_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_ERROR_STREAM_SKIPFIRST_THROTTLE(...)

#else
/**
 * \def ROSFMT_ERROR
 * \copydoc RCLCPP_LOG
 */
#define ROSFMT_ERROR(logger, ...)                                              \
  ROSFMT_LOG(RCUTILS_LOG_SEVERITY_ERROR, logger, __VA_ARGS__)

/**
 * \def ROSFMT_ERROR_ONCE
 * \copydoc RCLCPP_LOG_ONCE
 */
#define ROSFMT_ERROR_ONCE(logger, ...)                                         \
  ROSFMT_LOG_ONCE(RCUTILS_LOG_SEVERITY_ERROR, logger, __VA_ARGS__)

/**
 * \def ROSFMT_ERROR_EXPRESSION
 * \copydoc RCLCPP_LOG_EXPRESSION
 */
#define ROSFMT_ERROR_EXPRESSION(logger, expression, ...)                       \
  ROSFMT_LOG_EXPRESSION(RCUTILS_LOG_SEVERITY_ERROR, logger, expression,        \
                        __VA_ARGS__)

/**
 * \def ROSFMT_ERROR_FUNCTION
 * \copydoc RCLCPP_LOG_FUNCTION
 */
#define ROSFMT_ERROR_FUNCTION(logger, function, ...)                           \
  ROSFMT_LOG_FUNCTION(RCUTILS_LOG_SEVERITY_ERROR, logger, function, __VA_ARGS__)

/**
 * \def ROSFMT_ERROR_SKIPFIRST
 * \copydoc RCLCPP_LOG_SKIPFIRST
 */
#define ROSFMT_ERROR_SKIPFIRST(logger, ...)                                    \
  ROSFMT_LOG_SKIPFIRST(RCUTILS_LOG_SEVERITY_ERROR, logger, __VA_ARGS__)

/**
 * \def ROSFMT_ERROR_THROTTLE
 * \copydoc RCLCPP_LOG_THROTTLE
 */
#define ROSFMT_ERROR_THROTTLE(logger, clock, duration, ...)                    \
  ROSFMT_LOG_THROTTLE(RCUTILS_LOG_SEVERITY_ERROR, logger, clock, duration,     \
                      __VA_ARGS__)

/**
 * \def ROSFMT_ERROR_SKIPFIRST_THROTTLE
 * \copydoc RCLCPP_LOG_SKIPFIRST_THROTTLE
 */
#define ROSFMT_ERROR_SKIPFIRST_THROTTLE(logger, clock, duration, ...)          \
  ROSFMT_LOG_SKIPFIRST_THROTTLE(RCUTILS_LOG_SEVERITY_ERROR, logger, clock,     \
                                duration, __VA_ARGS__)

#endif

/** @name Logging macros for severity FATAL.
 */
#if (RCLCPP_LOG_MIN_SEVERITY > RCLCPP_LOG_MIN_SEVERITY_FATAL)
// empty logging macros for severity FATAL when being disabled at compile time
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_SKIPFIRST_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM_ONCE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM_EXPRESSION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM_FUNCTION(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM_SKIPFIRST(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM_THROTTLE(...)
/// Empty logging macro due to the preprocessor definition of
/// RCLCPP_LOG_MIN_SEVERITY.
#define ROSFMT_FATAL_STREAM_SKIPFIRST_THROTTLE(...)

#else
/**
 * \def ROSFMT_FATAL
 * \copydoc RCLCPP_LOG
 */
#define ROSFMT_FATAL(logger, ...)                                              \
  ROSFMT_LOG(RCUTILS_LOG_SEVERITY_FATAL, logger, __VA_ARGS__)

/**
 * \def ROSFMT_FATAL_ONCE
 * \copydoc RCLCPP_LOG_ONCE
 */
#define ROSFMT_FATAL_ONCE(logger, ...)                                         \
  ROSFMT_LOG_ONCE(RCUTILS_LOG_SEVERITY_FATAL, logger, __VA_ARGS__)

/**
 * \def ROSFMT_FATAL_EXPRESSION
 * \copydoc RCLCPP_LOG_EXPRESSION
 */
#define ROSFMT_FATAL_EXPRESSION(logger, expression, ...)                       \
  ROSFMT_LOG_EXPRESSION(RCUTILS_LOG_SEVERITY_FATAL, logger, expression,        \
                        __VA_ARGS__)

/**
 * \def ROSFMT_FATAL_FUNCTION
 * \copydoc RCLCPP_LOG_FUNCTION
 */
#define ROSFMT_FATAL_FUNCTION(logger, function, ...)                           \
  ROSFMT_LOG_FUNCTION(RCUTILS_LOG_SEVERITY_FATAL, logger, function, __VA_ARGS__)

/**
 * \def ROSFMT_FATAL_SKIPFIRST
 * \copydoc RCLCPP_LOG_SKIPFIRST
 */
#define ROSFMT_FATAL_SKIPFIRST(logger, ...)                                    \
  ROSFMT_LOG_SKIPFIRST(RCUTILS_LOG_SEVERITY_FATAL, logger, __VA_ARGS__)

/**
 * \def ROSFMT_FATAL_THROTTLE
 * \copydoc RCLCPP_LOG_THROTTLE
 */
#define ROSFMT_FATAL_THROTTLE(logger, clock, duration, ...)                    \
  ROSFMT_LOG_THROTTLE(RCUTILS_LOG_SEVERITY_FATAL, logger, clock, duration,     \
                      __VA_ARGS__)

/**
 * \def ROSFMT_FATAL_SKIPFIRST_THROTTLE
 * \copydoc RCLCPP_LOG_SKIPFIRST_THROTTLE
 */
#define ROSFMT_FATAL_SKIPFIRST_THROTTLE(logger, clock, duration, ...)          \
  ROSFMT_LOG_SKIPFIRST_THROTTLE(RCUTILS_LOG_SEVERITY_FATAL, logger, clock,     \
                                duration, __VA_ARGS__)

#endif

#endif // include guard
