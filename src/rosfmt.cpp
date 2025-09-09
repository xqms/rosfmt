// rosfmt - type-safe RCLCPP_* logging macros (precompiled parts)
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

#include <fmt/format.h>

#include <rosfmt/rosfmt.hpp>

namespace rosfmt
{
namespace internal
{

const char * vformat(fmt::string_view format_str, fmt::format_args args)
{
  static thread_local auto buf = [](){
      auto b = fmt::memory_buffer();
      b.reserve(512);
      return b;
    }();
  buf.clear();
  fmt::vformat_to(std::back_inserter(buf), format_str, args);
  buf.push_back(0);
  return buf.data();
}

}    // namespace internal
}  // namespace rosfmt
