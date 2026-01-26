#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FatFsSd.h"
#include "imu/MPU6050.h"
#include "recorder/Recorder.h"
#include "utils/Utils.h"

int main() {
    stdio_init_all();
    sleep_ms(3000); 
    
    Utils::init_hardware();
    Recorder recorder;

    while(true){
        if(Utils::is_button_clicked()){
            Utils::turnOn_green();
            std::cout << "\n--- Starting Flight Recorder ---\n" << std::endl;
            break;
        }
        sleep_ms(50);
    }

    MPU6050 mpu(i2c0, 4, 5); 
    Gyro_t current_gyro;


    while(true) {
        if(Utils::is_button_clicked()){
            Utils::turnOff_green();
            std::cout << "\n--- Stoping Flight Recorder ---\n" << std::endl;
            break;
        }

        mpu.getGyro(&current_gyro);


        recorder.log_data(current_gyro);

        printf("Logged: X:%d Y:%d Z:%d\n", current_gyro.gyro_x, current_gyro.gyro_y, current_gyro.gyro_z);

        sleep_ms(50); 
    }

    while(true) tight_loop_contents();
}
   