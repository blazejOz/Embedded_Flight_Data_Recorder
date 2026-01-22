#include "Recorder.h"


namespace FatFsNs {
    std::vector<SdCard> FatFs::SdCards;
}

extern "C" {
    size_t sd_get_num() { return 1; }
    sd_card_t *sd_get_by_num(size_t num) {
        // This must point to the config you defined in Recorder.h
        extern sd_card_t sd_card_config; 
        if (num == 0) return &sd_card_config;
        return nullptr;
    }
}

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

}
