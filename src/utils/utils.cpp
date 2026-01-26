#include "pico/stdlib.h"
#include <string>
#include <iostream>

#define RED_LED_PIN 15
#define GREEN_LED_PIN 14

#define BTN_PIN 13


namespace Utils
{
    void init_hardware()
    {
        // Setup Button
        gpio_init(BTN_PIN);
        gpio_set_dir(BTN_PIN, GPIO_IN);
        gpio_pull_up(BTN_PIN);

        // Setup LEDs
        gpio_init(GREEN_LED_PIN);
        gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
        gpio_put(GREEN_LED_PIN, 0); 

        gpio_init(RED_LED_PIN);
        gpio_set_dir(RED_LED_PIN, GPIO_OUT);
        gpio_put(RED_LED_PIN, 0);   

    }

    void turnOn_green(){
        gpio_put(GREEN_LED_PIN, 1);
    }

    void turnOff_green(){
        gpio_put(GREEN_LED_PIN, 0);
    }

    void handle_error(std::string msg)
    {
        turnOff_green();
        while(true){
            std::cout << msg << '\n';
            gpio_put(RED_LED_PIN, 1);  
            sleep_ms(500);
            gpio_put(RED_LED_PIN, 0);  
            sleep_ms(500);
        }
    }

    bool is_button_clicked()
    {
        if (gpio_get(BTN_PIN) == 0) {
            // Debounce
            sleep_ms(50);
            if (gpio_get(BTN_PIN) != 0) return false;

            uint32_t hold_time = 0;

            while(gpio_get(BTN_PIN) == 0){
                sleep_ms(100);
                hold_time += 100;

                if(hold_time >= 1500) {
                    std::cout << "button clicked" << std::endl;
                    while(gpio_get(BTN_PIN) == 0) sleep_ms(10);
                    return true;
                }
            }
        }
        return false;
    }

}