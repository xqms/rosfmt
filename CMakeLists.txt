
cmake_minimum_required(VERSION 3.0)
project(rosfmt)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rosconsole
)

find_package(fmt REQUIRED)

catkin_package(
	INCLUDE_DIRS include
	CATKIN_DEPENDS roscpp rosconsole
	LIBRARIES rosfmt9
)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
)

add_library(rosfmt9
	src/rosfmt.cpp
)
target_link_libraries(rosfmt9
	${catkin_LIBRARIES}
	fmt::fmt
)

if(CATKIN_ENABLE_TESTING)
	add_executable(simple_test
		test/test.cpp
	)
	target_link_libraries(simple_test rosfmt9)
	add_test(
		NAME SimpleTest
		COMMAND simple_test
	)
	add_custom_target(run_simple_test
		COMMAND simple_test
	)
	add_dependencies(run_tests run_simple_test)
endif()

install(
	DIRECTORY include/rosfmt/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(
	TARGETS rosfmt9
	DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)
