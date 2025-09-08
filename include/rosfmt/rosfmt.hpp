// rosfmt - type-safe RCLCPP_* logging macros
// Author: Max Schwarz <max.schwarz@ais.uni-bonn.de>

#ifndef ROSFMT_H
#define ROSFMT_H

#include <fmt/core.h>

#include <string>

#include <rosfmt/logging_macros.hpp>

#include <rclcpp/node.hpp>

namespace rosfmt {

std::string vformat(fmt::string_view format_str, fmt::format_args args);

template <typename... Args>
std::string format(const std::string &formatString, const Args &...args) {
  fmt::format_arg_store<fmt::format_context, Args...> as{args...};
  return rosfmt::vformat(formatString, as);
}

} // namespace rosfmt

#endif // include guard
