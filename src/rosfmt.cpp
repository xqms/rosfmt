// rosfmt - type-safe ROS_* logging macros (precompiled parts)
// Author: Max Schwarz <max.schwarz@ais.uni-bonn.de>

#include <rosfmt/rosfmt.h>

#include <fmt/format.h>

namespace rosfmt
{

std::string vformat(fmt::string_view format_str, fmt::format_args args)
{
	return fmt::vformat(format_str, args);
}

}
