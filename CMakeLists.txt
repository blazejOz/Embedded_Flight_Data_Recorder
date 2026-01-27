cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2_w CACHE STRING "Board type")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(Embedded_Flight_Recorder C CXX ASM)
pico_sdk_init()

add_executable(flrc 
        src/main.cpp
        src/imu/MPU6050.cpp
        src/recorder/Recorder.cpp
        src/utils/Utils.cpp
    )

target_include_directories(flrc PRIVATE src)
target_include_directories(flrc PRIVATE external_lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/include)

add_subdirectory(external_lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src build)

target_link_libraries(flrc
    pico_stdlib 
    pico_cyw43_arch_none
    hardware_i2c
    hardware_spi
    no-OS-FatFS-SD-SDIO-SPI-RPi-Pico
)

# Enable USB output (serial)
pico_enable_stdio_usb(flrc 1)
pico_enable_stdio_uart(flrc 0)
pico_add_extra_outputs(flrc)