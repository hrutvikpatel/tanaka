cmake_minimum_required(VERSION 3.14)
project(tanaka)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch CLI11
FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.3.2
)
FetchContent_MakeAvailable(CLI11)

# Fetch spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

# Automatically find all cpp files under src/
file(GLOB_RECURSE SOURCES
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(tanaka_daemon ${SOURCES})

target_link_libraries(tanaka_daemon PRIVATE
  spdlog::spdlog
  CLI11::CLI11
)

target_include_directories(tanaka_daemon PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)