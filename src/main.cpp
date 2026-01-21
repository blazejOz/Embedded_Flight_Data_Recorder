#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FatFsSd.h"
#include "imu/MPU6050.h"


#include <stdio.h>
#include <string.h>


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

int main() {
    stdio_init_all();
    sleep_ms(3000); 
    printf("\n--- Starting SD Card Test ---\n");

    // Initialize the driver
    sd_init_driver(); 

    // Add the card to the system
    FatFsNs::SdCard* card_p = FatFsNs::FatFs::add_sd_card(&sd_card_config);
    
    // Attempt to mount
    FRESULT fr = card_p->mount();
    if (fr != FR_OK) {
        printf("Mount FAILED! Error: %d\n", fr);
        while (true) tight_loop_contents();
    }
    printf("Mount SUCCESS!\n");

    // Create and write file
    FatFsNs::File file;
    fr = file.open("hello.txt", FA_WRITE | FA_CREATE_ALWAYS);
    
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

    while (true) {
        tight_loop_contents();
    }
}

namespace FatFsNs {
    std::vector<SdCard> FatFs::SdCards;
}

extern "C" {
    size_t sd_get_num() { return 1; }

    // Force the library to use the specific struct we defined
    sd_card_t *sd_get_by_num(size_t num) {
        if (num == 0) return &sd_card_config; 
        return nullptr;
    }
}
/*
int main()
{
    stdio_init_all();

    MPU6050 mpu(i2c0, 4, 5);

    Gyro_t data;
    while(true) {
        mpu.getGyro(&data);

        printf("X: %6d | Y: %6d | Z: %6d\n", data.gyro_x, data.gyro_y, data.gyro_z);
        sleep_ms(100);
    }



}
    */
   