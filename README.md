# Embedded_Flight_Data_Recorder
Embedded Flight Data Recorder (C++ / RP2350)

A  flight data recorder(aka "Black Box") built for the Raspberry Pi Pico 2 W (RP2350). This project captures real-time motion data from an MPU6050 IMU and logs it to an SD card using a custom C++ wrapper around the FatFs filesystem provided by carlk3(https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

**Status:** Active Development / Prototype

## Hardware Architecture

* **Microcontroller:** Raspberry Pi Pico 2 W
* **Sensor:** MPU6050 (6-axis Gyroscope & Accelerometer)
* **Storage:** MicroSD Card Module (SPI Mode)

### Wiring Diagram

| Component | Pin Label | Pico Pin | Function |
| :--- | :--- | :--- | :--- |
| **MPU6050** | SDA | GP4 | I2C Data |
| **MPU6050** | SCL | GP5 | I2C Clock |
| **MPU6050** | VCC | 3V3 | Power |
| **MPU6050** | GND | GND | Ground |
| | | | |
| **SD Card** | DI (MOSI)| GP19 | SPI TX |
| **SD Card** | DO (MISO)| GP16 | SPI RX |
| **SD Card** | SCK | GP18 | SPI Clock |
| **SD Card** | CS | GP17 | Chip Select |
| **SD Card** | VCC | 3V3 | Power |
| **SD Card** | GND | GND | Ground |

## Software Design

The project uses an Object-Oriented approach to manage hardware peripherals:
* **`Recorder` Class:** Encapsulates the file system logic, handling mounting, file creation, and safe data logging.
* **`MPU6050` Class:** manages I2C communication and raw data extraction.
* **Safe Shutdown:** Includes a timer-based mechanism (currently set to 10s) to safely close files before power loss, preventing data corruption.

### External Dependencies

This project utilizes the **no-OS-FatFS-SD-SDIO-SPI-RPi-Pico** library for robust SD card communication over SPI.
* **Library Author:** Carl John Kugler III
* **Source:** [https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SDIO-SPI-RPi-Pico)

## Build Instructions

Built using the standard Raspberry Pi Pico SDK and CMake
For Nixos users use flake - nix develop

```bash
mkdir build
cd build
cmake .. 
make
```
