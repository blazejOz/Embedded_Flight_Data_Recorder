#pragma once

#include <iostream>
#include <string.h>

#include "../imu/MPU6050.h"
#include "FatFsSd.h"



static spi_t spi_bus = {
    .hw_inst = spi0,
    .miso_gpio = 16, // DO
    .mosi_gpio = 19, // DI
    .sck_gpio = 18,  // SCLK
    .baud_rate = 1000 * 1000, 
    .set_drive_strength = true,
    .mosi_gpio_drive_strength = GPIO_DRIVE_STRENGTH_12MA,
    .sck_gpio_drive_strength = GPIO_DRIVE_STRENGTH_12MA
};

static sd_spi_if_t spi_if = {
    .spi = &spi_bus,
    .ss_gpio = 17    // CS
};

static sd_card_t sd_card_config = {
    .type = SD_IF_SPI,
    .spi_if_p = &spi_if,
    .use_card_detect = false // Ignore the Card Detect pin
};



class Recorder {
public:
    FatFsNs::SdCard* card_p = nullptr;
    Recorder();

private:
    int init_sensor();

};