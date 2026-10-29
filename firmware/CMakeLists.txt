
cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico CACHE STRING "Board type")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(ProgramKeyFirmware C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

pico_sdk_init()

set(PROGRAM_KEY_TARGET "main" CACHE STRING "Firmware Target")
set_property(CACHE PROGRAM_KEY_TARGET PROPERTY STRINGS main mpr121)

if(PROGRAM_KEY_TARGET STREQUAL "main")
    set(PROGRAM_KEY_SOURCES
        main.cpp
        ../src/keyboard.cpp
        ../src/keymap.cpp
    )
elseif(PROGRAM_KEY_TARGET STREQUAL "mpr121")
    set(PROGRAM_KEY_SOURCES
        tests/test_mpr121.cpp
    )
else()
    message(FATAL_ERROR "Unknown PROGRAM_KEY_TARGET")
endif()

add_executable(program_key_firmware ${PROGRAM_KEY_SOURCES})

target_include_directories (program_key_firmware PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(program_key_firmware
    pico_stdlib
    hardware_i2c
)

pico_enable_stdio_usb(program_key_firmware 1)
pico_enable_stdio_uart(program_key_firmware 0)

pico_add_extra_outputs(program_key_firmware)

