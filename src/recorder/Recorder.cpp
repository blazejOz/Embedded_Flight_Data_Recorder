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
    init_sensor();
}

int Recorder::init_sensor()
{
    // Initialize the driver
    sd_init_driver(); 

    // Add the card to the system
    this->card_p = FatFsNs::FatFs::add_sd_card(&sd_card_config);

    // Attempt to mount
    FRESULT fr = this->card_p->mount();
    if (fr != FR_OK) {
        printf("Mount FAILED! Error: %d\n", fr);
        return fr;
    }
    printf("Mount SUCCESS!\n");
    return fr;

}

int Recorder::write_to_sd()
{
    // Create and write file
    FatFsNs::File file;
    FRESULT fr = file.open("hello.txt", FA_WRITE | FA_CREATE_ALWAYS);
    
    if (fr == FR_OK) {
        file.puts("Hello from Pico 2 W!\n");
        file.puts("This file was created using the C++ Wrapper.\n");
        file.close();
        printf("SUCCESS: 'hello.txt' created.\n");
    } else {
        printf("File open FAILED! Error: %d\n", fr);
    }

    card_p->unmount();
    printf("Done. You can unplug the card now.\n");


}
