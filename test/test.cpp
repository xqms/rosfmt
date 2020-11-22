// Simple compilation test
// Author: Max Schwarz <max.schwarz@ais.uni-bonn.de>

#include <rosfmt/full.h>

int main(int argc, char** argv)
{
	ROSFMT_INFO("Hello world");
	ROSFMT_INFO("This is five: {}", 5);
	return 0;
}
