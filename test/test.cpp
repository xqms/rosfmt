// Simple compilation test
// Author: Max Schwarz <max.schwarz@ais.uni-bonn.de>

#include <rosfmt/full.hpp>

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);

	rclcpp::Logger logger = rclcpp::get_logger("test_logger");

	ROSFMT_INFO(logger, "Hello world");
	ROSFMT_INFO(logger, "This is five: {}", 5);
	return 0;
}
