cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Embedded_Flight_Recorder C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

#Point CMake to the local FreeRTOS submodule and import it
set(FREERTOS_KERNEL_PATH "${CMAKE_CURRENT_LIST_DIR}/external_lib/FreeRTOS-Kernel" CACHE PATH "")
include(FreeRTOS_Kernel_import.cmake)

# Add no-OS-FatFS Library
add_subdirectory(external_lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/src build)

#Create the executable - flrc
add_executable(flrc
    src/main.cpp
    src/imu/MPU6050.cpp
    src/recorder/Recorder.cpp
    src/utils/Utils.cpp
)

# Add FreeRTOSConfig.h to the kernel 
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src)
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)


target_include_directories(flrc PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/external_lib/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico/include
)

#Link libraries directly to flrc
target_link_libraries(flrc
    pico_stdlib
    hardware_i2c
    hardware_spi
    hardware_timer
    pico_unique_id
    pico_multicore
    no-OS-FatFS-SD-SDIO-SPI-RPi-Pico
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

#Enable I/O over USB disable UART
pico_enable_stdio_uart(flrc 0)
pico_enable_stdio_usb(flrc 1)

#Generate extra outputs like the .uf2 file
pico_add_extra_outputs(flrc)