# embedded_avionics_logger
[![CI](https://github.com/blazejOz/embedded_avionics_logger/actions/workflows/build.yml/badge.svg)](https://github.com/blazejOz/embedded_avionics_logger/actions)

Embedded Avionics Data Logger (C++ / RP2350)

A high-reliability **Flight Data Recorder ("Black Box")** built for the **Raspberry Pi Pico 2 (RP2350)**. 

This project captures real-time motion data from an **MPU6050 IMU** and logs it to an SD card via the **no-OS-FatFS-SD-SDIO-SPI-RPi-Pico** library. To guarantee zero data loss during high-latency SPI writes to the SD card, the system leverages **FreeRTOS** to handle everything in the background. By splitting the work into two independent threads—one that reads the sensor and another that writes to the card—the recorder never drops a single data point.


![Recorder Demo](assets/demo.gif)

## Hardware Architecture

* **Microcontroller:** Raspberry Pi Pico 2
* **Sensor:** MPU6050 (6-axis Gyroscope & Accelerometer)
* **Storage:** MicroSD Card Module (SPI Mode)
* **Interface:** Tactile Button & Status LEDs


## Software Design

The project uses an Object-Oriented approach to manage hardware peripherals:
* **`Recorder` Class:** Encapsulates the file system logic, handling mounting, file creation, and safe data logging.
* **`MPU6050` Class:** manages I2C communication and raw data extraction.
* **`Utils` Namespace:** button, LED and error handling.

### External Dependencies

This project utilizes the **no-OS-FatFS-SD-SDIO-SPI-RPi-Pico** library for robust SD card communication over SPI.
* **Library Author:** Carl John Kugler III
* **Source:** [https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

This project utilizes the **FreeRTOS-Kernel** library for mutithreading.
* **Library Author:** FreeRTOS
* **Source:** [https://github.com/FreeRTOS/FreeRTOS-Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel)

## Build Instructions

Built using the standard Raspberry Pi Pico SDK and CMake

```bash
cmake -B build
cmake --build build
```

## Roadmap / Todo

- [x] **Basic SD Card Logging** (CSV format)
- [x] **Manual Start/Stop Control** (Button + LED feedback)
- [x] **Gyroscope Data Capture** (X/Y/Z)
- [x] **Add Accelerometer Data:** Expand MPU6050 driver to capture acceleration.
- [x] **Error Codes:** Instead of just one LED, use different blink patterns.
- [x] **Timestamps:** Add millisecond precision timestamps to the log.
- [x] **FreeRTOS:** Refactor the codebase into prioritized Tasks (Sensing vs. Logging) using FreeRTOS to prevent SD card latency.
