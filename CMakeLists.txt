
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
	URL https://github.com/fmtlib/fmt/releases/download/6.0.0/fmt-6.0.0.zip
	URL_HASH SHA256=b4a16b38fa171f15dbfb958b02da9bbef2c482debadf64ac81ec61b5ac422440
	CONFIGURE_COMMAND ""

	# We touch all downloaded files, otherwise they get some timestamp in the
	# past and may confuse the dependency tracking below.
	BUILD_COMMAND find <SOURCE_DIR> -type f -exec touch {} +
	INSTALL_COMMAND ""
)

# Now extract the needed files. We need to copy headers to the devel space
# b/c of catkin policies (they count as "generated headers").
ExternalProject_Get_property(fmt SOURCE_DIR)
set(fmt_SOURCE_DIR "${SOURCE_DIR}")
set(fmt_HEADER_DEST "${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}")

file(MAKE_DIRECTORY ${fmt_HEADER_DEST})
foreach(FILE chrono.h color.h compile.h core.h format-inl.h format.h locale.h ostream.h posix.h printf.h ranges.h safe-duration-cast.h)
	set(in "${fmt_SOURCE_DIR}/include/fmt/${FILE}")
	set(out "${fmt_HEADER_DEST}/fmt/${FILE}")
	list(APPEND fmt_HEADERS_OUT ${out})

	set_source_files_properties(${in} PROPERTIES GENERATED TRUE)
	set_source_files_properties(${out} PROPERTIES GENERATED TRUE)

	add_custom_command(
		OUTPUT ${out}
		DEPENDS ${in} fmt
		COMMAND cmake -E copy_if_different "${in}" "${out}"
	)
endforeach()

add_custom_target(fmt_headers
	DEPENDS ${fmt_HEADERS_OUT}
)

catkin_package(
	INCLUDE_DIRS include ${fmt_HEADER_DEST}
	CATKIN_DEPENDS roscpp rosconsole
	LIBRARIES rosfmt
)

include_directories(
	${fmt_HEADER_DEST}
	${catkin_INCLUDE_DIRS}
	include
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
	src/rosfmt.cpp
)
target_link_libraries(rosfmt
	${catkin_LIBRARIES}
)
add_dependencies(rosfmt fmt fmt_headers)

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
