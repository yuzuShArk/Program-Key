cmake_minimum_required(VERSION 3.20)

project(ProgramKey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(program_key
    src/main.cpp
    src/keymap.cpp
    src/keyboard.cpp
)

target_include_directories(program_key
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
