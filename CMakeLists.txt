cmake_minimum_required(VERSION 3.16)
project(HelloQt LANGUAGES CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt Widgets module
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add executable
add_executable(HelloQt main.cpp)

# Link Qt libraries
target_link_libraries(HelloQt PRIVATE Qt6::Widgets)
