#include "Recorder.h"


// HARDWARE SETUP

spi_t spi_bus = {
    .hw_inst = spi0,
    .miso_gpio = 16, // DO
    .mosi_gpio = 19, // DI
    .sck_gpio = 18,  // SCLK
    .baud_rate = 12 * 1000 * 1000, 
    .set_drive_strength = true,
    .mosi_gpio_drive_strength = GPIO_DRIVE_STRENGTH_12MA,
    .sck_gpio_drive_strength = GPIO_DRIVE_STRENGTH_12MA
};

sd_spi_if_t spi_if = {
    .spi = &spi_bus,
    .ss_gpio = 17    // CS
};

sd_card_t sd_card_config = {
    .type = SD_IF_SPI,
    .spi_if_p = &spi_if,
    .use_card_detect = false // Ignore the Card Detect pin
};

// "GLUE" CODE 
// NEEDED TO WORK WITH no-osFatFS lib

namespace FatFsNs {
    std::vector<SdCard> FatFs::SdCards;
}

extern "C" {
    size_t sd_get_num() { return 1; }
    sd_card_t *sd_get_by_num(size_t num) {
        extern sd_card_t sd_card_config; 
        if (num == 0) return &sd_card_config;
        return nullptr;
    }
}


// CLASS LOGIC

Recorder::Recorder()
{
    printf("\n--- CRATED OBJECT RECORDER ---\n");
    init_sd();
}

int Recorder::init_sd()
{
    // Initialize the driver
    sd_init_driver(); 

    // Add the card to the system
    this->card_p = FatFsNs::FatFs::add_sd_card(&sd_card_config);
    return 0;
}

int Recorder::log_data(const Gyro_t& data) {
    // 1. Ensure mounted
    FRESULT fr = this->card_p->mount();
    if (fr != FR_OK) return (int)fr;

    FatFsNs::File file;
    

    fr = file.open("0:flight_data.csv", FA_WRITE | FA_OPEN_APPEND);
    
    if (fr == FR_OK) {
        char buffer[64];
        sprintf(buffer, "%d, %d, %d\n", data.gyro_x, data.gyro_y, data.gyro_z);
        file.puts(buffer);

        file.close();
    } else {
        printf("Log failed: %d\n", fr);
    }
    
    // this->card_p->unmount(); 
    
    return (int)fr;
}

