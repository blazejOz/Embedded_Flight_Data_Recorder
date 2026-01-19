#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "imu/MPU6050.h"



int main()
{

    MPU6050 mpu(i2c0, 4, 5);

}