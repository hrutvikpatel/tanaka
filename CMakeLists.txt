cmake_minimum_required(VERSION 3.10)
project(tanaka)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(spdlog REQUIRED)

# Add executable
add_executable(tanaka_daemon 
    main.cpp
    utils/logger.cpp
)

# Link libraries
target_link_libraries(tanaka_daemon PRIVATE
    spdlog::spdlog
)
