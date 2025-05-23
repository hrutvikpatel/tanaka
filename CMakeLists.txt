cmake_minimum_required(VERSION 3.14)
project(tanaka)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(CLI11)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  tomlplusplus
  GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
  GIT_TAG v3.4.0
)
FetchContent_Populate(tomlplusplus)

FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(SQLiteCpp)

enable_testing()

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(tanaka_lib ${SOURCES})

target_link_libraries(tanaka_lib PUBLIC spdlog::spdlog CLI11::CLI11 SQLiteCpp)
target_include_directories(tanaka_lib
  PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${tomlplusplus_SOURCE_DIR}/include
)

add_executable(tanaka_daemon src/main.cpp)
target_link_libraries(tanaka_daemon PRIVATE tanaka_lib)

# Optional tests
option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()