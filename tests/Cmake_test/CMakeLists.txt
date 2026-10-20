cmake_minimum_required(VERSION 3.20)
project(CMake_test LANGUAGES CXX)
add_executable(CMake_test_output main.cpp)
target_compile_features(CMake_test_output PRIVATE cxx_std_20)
