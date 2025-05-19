file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(test_ui ${TEST_SOURCES})

target_link_libraries(test_ui PRIVATE Catch2::Catch2WithMain CLI11::CLI11 tanaka_lib)
target_include_directories(test_ui PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(CTest)
include(Catch)
catch_discover_tests(test_ui)