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
  GIT_TAG v1.11.0  # use latest stable release
)
FetchContent_MakeAvailable(spdlog)

# Source files
set(SOURCES
    main.cpp
    ui/ui.cpp
    utils/logger.cpp
)

add_executable(tanaka_daemon ${SOURCES})

# Link libraries
target_link_libraries(tanaka_daemon PRIVATE
    spdlog::spdlog
    CLI11::CLI11
)

# Include your own headers
target_include_directories(tanaka_daemon PRIVATE
    ${PROJECT_SOURCE_DIR}/cli
    ${PROJECT_SOURCE_DIR}/utils
)