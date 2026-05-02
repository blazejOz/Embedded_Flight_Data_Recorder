#include "Utils.h"
#include "../pinout.h"
#include <iostream>


namespace Utils
{
    void init(
        uint START_BTN_PIN, 
        uint GREEN_LED_PIN,
        uint RED_LED_PIN)
    {
        // Setup Button
        gpio_init(START_BTN_PIN);
        gpio_set_dir(START_BTN_PIN, GPIO_IN);
        gpio_pull_up(START_BTN_PIN);

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

    void turnOn_red(){
        gpio_put(RED_LED_PIN, 1);
    }

    void handle_error(const char* msg)
    {
        turnOff_green();

        printf("ERROR: %s\n", msg);

        while(true){
            gpio_put(RED_LED_PIN, 1);  
            sleep_ms(500);
            gpio_put(RED_LED_PIN, 0);  
            sleep_ms(500);
        }
    }

    bool is_button_clicked()
    {
        if (gpio_get(START_BTN_PIN) == 0) {
            // Debounce
            sleep_ms(50);
            if (gpio_get(START_BTN_PIN) != 0) return false;

            uint32_t hold_time = 0;

            while(gpio_get(START_BTN_PIN) == 0){
                sleep_ms(100);
                hold_time += 100;

                if(hold_time >= 1500) {
                    printf("button clicked\n");
                    while(gpio_get(START_BTN_PIN) == 0) sleep_ms(10);
                    return true;
                }
            }
        }
        return false;
    }

}