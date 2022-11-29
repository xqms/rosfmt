
rosfmt
======

`rosfmt` is a ROS wrapper around the awesome [fmt] library, which offers
modern C++11 type-safe formatting strings.

TLDR: Instead of

```C++
#include <ros/console.h>

ROS_INFO("Here is my string: %s. And a number: %llu",
    my_string.c_str(), my_number
);
```

you can now write:

```C++
#include <rosfmt/rosfmt.h>

ROSFMT_INFO("Here is my string: {}. And a number: {}",
    my_string, my_number
);
```

For more complicated messages, you can use named arguments:

```C++
ROSFMT_INFO("Here is my string: {str}. And a number: {num}",
    fmt::arg("str", my_string),
    fmt::arg("num", my_number)
);
```

Using `rosfmt/full.h` you can print types with `std::ostream` operators
(ROS messages, Eigen types) and ranges such as `std::vector`:

```C++
#include <rosfmt/full.h>

auto x = Eigen::Matrix3d::Identity();
ROSFMT_INFO("My matrix x:\n{}", x);
```

Of course, you can also use fmt's API directly:

```C++
std::string str = fmt::format("my string: {}", my_string);
```

See the [fmt documentation] for more details about fmt's features. For example,
you can easily define printing routines for your own data structures.

[fmt]: https://github.com/fmtlib/fmt
[fmt documentation]: http://fmtlib.net/

Usage
-----

Just depend on the `rosfmt` catkin package as usual. One catch is that `fmt`
requires C++11, so you need to enable that:

```CMake
cmake_minimum_required(VERSION 3.0)
project(my_package)

find_package(catkin REQUIRED COMPONENTS
	rosfmt
	roscpp
	rosconsole # might be required in older versions of rosfmt
)

catkin_package()
include_directories(${catkin_INCLUDE_DIRS})

# Important: enable C++11
set(CMAKE_CXX_STANDARD 11)

add_executable(my_node
	src/my_node.cpp
)
target_link_libraries(my_node
	${catkin_LIBRARIES}
)
```

License
-------

`rosfmt` and the underlying `fmt` library are licensed under the BSD-2 license.
