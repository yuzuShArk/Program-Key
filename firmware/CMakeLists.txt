
cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico CACHE STRING "Board type")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(ProgramKeyFirmware C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

pico_sdk_init()

add_executable(program_key_firmware
    main.cpp
    ../src/keyboard.cpp
    ../src/keymap.cpp
)

target_include_directories (program_key_firmware PRIVATE
    ../include/
)

target_link_libraries(program_key_firmware
    pico_stdlib
)

pico_enable_stdio_usb(program_key_firmware 1)
pico_enable_stdio_uart(program_key_firmware 0)

pico_add_extra_outputs(program_key_firmware)

