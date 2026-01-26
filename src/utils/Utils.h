#pragma once
#include <string>
#include "pico/stdlib.h"

namespace Utils {
    // Just the declarations go here!
    
    void init_hardware();
    void turnOn_green();
    void turnOff_green();
    void handle_error(const char* msg);
    
    // Returns true if button is held for > 2 seconds
    bool is_button_clicked();
}