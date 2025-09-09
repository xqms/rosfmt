// rosfmt - type-safe RCLCPP_* logging macros
//
// Copyright 2025 Max Schwarz <max.schwarz@ais.uni-bonn.de>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef ROSFMT__ROSFMT_HPP_
#define ROSFMT__ROSFMT_HPP_

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

template <class... Args>
[[maybe_unused]]
std::string formatThrottle(const std::chrono::milliseconds &duration,
                           const char *format, const Args &...args) {
  return ::rosfmt::format(format, args...);
}
template <class... Args>
[[maybe_unused]]
std::string formatThrottle(const char *format, const Args &...args) {
  return ::rosfmt::format(format, args...);
}

}  // namespace rosfmt

#endif  // ROSFMT__ROSFMT_HPP_
