#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FatFsSd.h"
#include "imu/MPU6050.h"
#include "recorder/Recorder.h"

int main() {
    stdio_init_all();
    sleep_ms(3000); 
    
    printf("\n--- Starting SD Card Test ---\n");

    Recorder recorder;

    while(true) {
        tight_loop_contents(); 
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
   