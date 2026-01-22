#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FatFsSd.h"
#include "imu/MPU6050.h"
#include "recorder/Recorder.h"

int main() {
    stdio_init_all();
    sleep_ms(3000); 
    
    printf("\n--- Starting Flight Recorder ---\n");

    Recorder recorder;
    MPU6050 mpu(i2c0, 4, 5); 
    Gyro_t current_gyro;

    //record for 10s
    absolute_time_t end_time = make_timeout_time_ms(10000);
    while(get_absolute_time() < end_time) {
        mpu.getGyro(&current_gyro);


        recorder.log_data(current_gyro);

        printf("Logged: X:%d Y:%d Z:%d\n", current_gyro.gyro_x, current_gyro.gyro_y, current_gyro.gyro_z);

        sleep_ms(50); 
    }

    printf("10 Seconds Done. SAFE TO UNPLUG.\n");
    while(true) tight_loop_contents();
}
   