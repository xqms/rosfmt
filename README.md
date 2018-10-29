
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

Of course, you can also use fmt's API directly:

```C++
std::string str = fmt::format("my string: {}", my_string);
```

See the [fmt documentation] for more details about fmt's features. For example,
you can easily define printing routines for your own data structures.

[fmt]: https://github.com/fmtlib/fmt
[fmt documentation]: http://fmtlib.net/

License
-------

`rosfmt` and the underlying `fmt` library are licensed under the BSD-2 license.
