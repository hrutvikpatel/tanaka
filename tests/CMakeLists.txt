# Collect all .cpp test files
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

message(STATUS "Test sources:")
foreach(src ${TEST_SOURCES})
    message(STATUS "  ${src}")
endforeach()

# Create the test executable
add_executable(tests ${TEST_SOURCES})

# Link libraries: Catch2 (with main), CLI11, your core lib
target_link_libraries(tests
  PRIVATE
    CLI11::CLI11
    tanaka_lib
    gtest
    gmock
    gtest_main
)

# Include dirs for headers (including toml++)
target_include_directories(tests
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${tomlplusplus_SOURCE_DIR}/include
)

# Enable test discovery
include(GoogleTest)
gtest_discover_tests(tests)