cmake_minimum_required(VERSION 3.13)

# set(PICO_BOARD pico2_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(Embedded_Flight_Recorder C CXX ASM)
pico_sdk_init()

add_executable(flrc 
        src/main.cpp
        src/imu/MPU6050.cpp
    )

target_include_directories(flrc PRIVATE src)

target_link_libraries(flrc
    pico_stdlib 
    pico_cyw43_arch_none
    hardware_adc
    hardware_i2c
)

# Enable USB output (serial)
pico_enable_stdio_usb(flrc 1)
pico_enable_stdio_uart(flrc 0)
pico_add_extra_outputs(flrc)