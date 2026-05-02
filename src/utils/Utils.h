#pragma once
#include <string>
#include "pico/stdlib.h"

namespace Utils {
    
    void init(
        uint START_BTN_PIN, 
        uint GREEN_LED_PIN,
        uint RED_LED_PIN
    );
    void turnOn_green();
    void turnOff_green();
    void turnOn_red();
    void handle_error(const char* msg);
    
    // Returns true if button is held for > 2 seconds
    bool is_button_clicked();
}