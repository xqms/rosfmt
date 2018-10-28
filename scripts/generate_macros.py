#!/usr/bin/python
# Adapted from rosconsole's generate_macros.py (license below)

# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

import os
import sys

def add_macro(f, caps_name, enum_name):
    f.write('#if (ROSCONSOLE_MIN_SEVERITY > ROSCONSOLE_SEVERITY_%s)\n' %(caps_name))
    f.write('#define ROSFMT_%s(...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_NAMED(name, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_COND(cond, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_COND_NAMED(cond, name, ...)\n' %(caps_name))

    f.write('#define ROSFMT_%s_ONCE(...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_ONCE_NAMED(name, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_THROTTLE(period, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_THROTTLE_NAMED(period, name, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_DELAYED_THROTTLE(period, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_DELAYED_THROTTLE_NAMED(period, name, ...)\n' %(caps_name))

    f.write('#define ROSFMT_%s_FILTER(filter, ...)\n' %(caps_name))
    f.write('#define ROSFMT_%s_FILTER_NAMED(filter, name, ...)\n' %(caps_name))
    f.write('#else\n')
    f.write('#define ROSFMT_%s(...) ROSFMT_LOG(::ros::console::levels::%s, ROSCONSOLE_DEFAULT_NAME, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_NAMED(name, ...) ROSFMT_LOG(::ros::console::levels::%s, std::string(ROSCONSOLE_NAME_PREFIX) + "." + name, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_COND(cond, ...) ROSFMT_LOG_COND(cond, ::ros::console::levels::%s, ROSCONSOLE_DEFAULT_NAME, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_COND_NAMED(cond, name, ...) ROSFMT_LOG_COND(cond, ::ros::console::levels::%s, std::string(ROSCONSOLE_NAME_PREFIX) + "." + name, __VA_ARGS__)\n' %(caps_name, enum_name))

    f.write('#define ROSFMT_%s_ONCE(...) ROSFMT_LOG_ONCE(::ros::console::levels::%s, ROSCONSOLE_DEFAULT_NAME, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_ONCE_NAMED(name, ...) ROSFMT_LOG_ONCE(::ros::console::levels::%s, std::string(ROSCONSOLE_NAME_PREFIX) + "." + name, __VA_ARGS__)\n' %(caps_name, enum_name))

    f.write('#define ROSFMT_%s_THROTTLE(period, ...) ROSFMT_LOG_THROTTLE(period, ::ros::console::levels::%s, ROSCONSOLE_DEFAULT_NAME, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_THROTTLE_NAMED(period, name, ...) ROSFMT_LOG_THROTTLE(period, ::ros::console::levels::%s, std::string(ROSCONSOLE_NAME_PREFIX) + "." + name, __VA_ARGS__)\n' %(caps_name, enum_name))

    f.write('#define ROSFMT_%s_DELAYED_THROTTLE(period, ...) ROSFMT_LOG_DELAYED_THROTTLE(period, ::ros::console::levels::%s, ROSCONSOLE_DEFAULT_NAME, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_DELAYED_THROTTLE_NAMED(period, name, ...) ROSFMT_LOG_DELAYED_THROTTLE(period, ::ros::console::levels::%s, std::string(ROSCONSOLE_NAME_PREFIX) + "." + name, __VA_ARGS__)\n' %(caps_name, enum_name))

    f.write('#define ROSFMT_%s_FILTER(filter, ...) ROSFMT_LOG_FILTER(filter, ::ros::console::levels::%s, ROSCONSOLE_DEFAULT_NAME, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#define ROSFMT_%s_FILTER_NAMED(filter, name, ...) ROSFMT_LOG_FILTER(filter, ::ros::console::levels::%s, std::string(ROSCONSOLE_NAME_PREFIX) + "." + name, __VA_ARGS__)\n' %(caps_name, enum_name))
    f.write('#endif\n\n')

f = open(os.path.join(os.path.dirname(__file__), '../include/rosfmt/macros_generated.h'), 'w')

f.write("// !!!!!!!!!!!!!!!!!!!!!!! This is a generated file, do not edit manually\n\n")

add_macro(f, "DEBUG", "Debug")
add_macro(f, "INFO", "Info")
add_macro(f, "WARN", "Warn")
add_macro(f, "ERROR", "Error")
add_macro(f, "FATAL", "Fatal")
