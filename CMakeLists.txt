
cmake_minimum_required(VERSION 3.14.4)
project(rosfmt)

find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(fmt REQUIRED)

add_library(rosfmt SHARED
    src/rosfmt.cpp
)
target_include_directories(rosfmt PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)
target_link_libraries(rosfmt PUBLIC
    rclcpp::rclcpp
    fmt::fmt
)
target_compile_features(rosfmt PUBLIC cxx_std_20)

install(TARGETS rosfmt
    EXPORT export_rosfmt
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include/${PROJECT_NAME})

ament_export_targets(export_rosfmt HAS_LIBRARY_TARGET)
ament_export_dependencies(rclcpp fmt)

if(BUILD_TESTING)
    add_executable(simple_test
        test/test.cpp
    )
    target_link_libraries(simple_test PRIVATE rosfmt)
    add_test(
        NAME SimpleTest
        COMMAND simple_test
    )
    add_custom_target(run_simple_test
        COMMAND simple_test
    )

    find_package(ament_lint_auto REQUIRED)
    ament_lint_auto_find_test_dependencies()
endif()

ament_package()
