
cmake_minimum_required(VERSION 3.0)
project(rosfmt)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rosconsole
)

# Get fmt from an official release
include(ExternalProject)
ExternalProject_Add(
	fmt
	URL https://github.com/fmtlib/fmt/releases/download/5.2.1/fmt-5.2.1.zip
	URL_HASH SHA256=43894ab8fe561fc9e523a8024efc23018431fa86b95d45b06dbe6ddb29ffb6cd
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)

# Now extract the needed files. We need to copy headers to the devel space
# b/c of catkin policies (they count as "generated headers").
ExternalProject_Get_property(fmt SOURCE_DIR)
set(fmt_SOURCE_DIR "${SOURCE_DIR}")
set(fmt_HEADER_DEST "${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}")

file(MAKE_DIRECTORY ${fmt_HEADER_DEST})
foreach(FILE color.h core.h format-inl.h format.h ostream.h posix.h printf.h ranges.h time.h)
	set(in "${fmt_SOURCE_DIR}/include/fmt/${FILE}")
	set(out "${fmt_HEADER_DEST}/fmt/${FILE}")
	set(fmt_HEADERS_OUT ${fmt_HEADERS_OUT} ${out})

	set_source_files_properties(${in} PROPERTIES GENERATED TRUE)

	add_custom_command(
		OUTPUT ${out}
		DEPENDS ${in}
		COMMAND cmake -E copy_if_different "${in}" "${out}"
	)
endforeach()

catkin_package(
	INCLUDE_DIRS include ${fmt_HEADER_DEST}
	CATKIN_DEPENDS roscpp rosconsole
	LIBRARIES rosfmt
)

include_directories(
	${catkin_INCLUDE_DIRS}
	include ${fmt_HEADER_DEST}
)

set(CMAKE_CXX_STANDARD 11)

set_source_files_properties(
	${fmt_SOURCE_DIR}/src/format.cc
	${fmt_SOURCE_DIR}/src/posix.cc
	PROPERTIES GENERATED TRUE
)

add_library(rosfmt
	${fmt_HEADERS_OUT}
	${fmt_SOURCE_DIR}/src/format.cc
	${fmt_SOURCE_DIR}/src/posix.cc
)
target_link_libraries(rosfmt
	${catkin_LIBRARIES}
)
add_dependencies(rosfmt fmt)

add_executable(simple_test
	test/test.cpp
)
target_link_libraries(simple_test rosfmt)

install(
	DIRECTORY ${fmt_HEADER_DEST}/fmt/
	DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/fmt
)
install(
	DIRECTORY include/rosfmt/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(
	TARGETS rosfmt
	DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)
