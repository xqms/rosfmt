// Simple compilation test
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

#include <rosfmt/full.hpp>

using namespace std::chrono_literals;

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    rclcpp::Logger logger = rclcpp::get_logger("test_logger");

    ROSFMT_INFO(logger, "Hello world");
    ROSFMT_INFO(logger, "This is five: {}", 5);

    rclcpp::Node node{"test_node"};

    ROSFMT_INFO(node, "Hello world from a node");

    ROSFMT_INFO_THROTTLE(node, 2s, "Throttled");
    ROSFMT_INFO_THROTTLE(node.get_logger(), *node.get_clock(), 2s, "Throttled");

    return 0;
}
