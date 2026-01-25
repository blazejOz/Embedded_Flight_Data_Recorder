#include "pico/stdlib.h"
#include <string>
#include <iostream>

#define RED_LED_PIN 15
#define GREEN_LED_PIN 14


bool green_led{false};
bool red_led{false};
namespace Utils
{
    void handle_error(std::string msg)
    {
        gpio_init(RED_LED_PIN);
        gpio_set_dir(RED_LED_PIN, GPIO_OUT);
        red_led = true;
        green_led = false;

        while(red_led){
            std::cout << msg << '\n';
            gpio_put(RED_LED_PIN, 1);  
            sleep_ms(100);
            gpio_put(RED_LED_PIN, 0);  
            sleep_ms(100);
        }
    }

    void turnOn_green()
    {
        gpio_init(GREEN_LED_PIN);
        gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
        green_led = true;

        while(green_led){
            gpio_put(GREEN_LED_PIN, 1);  
            sleep_ms(1000);
        }
    }

}