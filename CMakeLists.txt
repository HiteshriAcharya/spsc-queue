cmake_minimum_required(VERSION 3.20)

project(spsc_queue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spsc_tests tests/test_spsc.cpp)

target_include_directories(spsc_tests PRIVATE include)