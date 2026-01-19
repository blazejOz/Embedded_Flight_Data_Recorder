#pragma once
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <cstdio>  
#include <cstdint> 

//I2C 
#define MPU6050_ADDR        0x68

//REGISTRIES
#define REG_PWR_MGMT_1      0x6B
#define REG_WHO_AM_I        0x75

#define	REG_GYRO_XOUT_H		0x43
#define	REG_GYRO_YOUT_H		0x45
#define	REG_GYRO_ZOUT_H		0x47

// MPU6050 ID 
#define WHO_AM_I_VALUE      0x68

/*
    MPU6050 - module is a compact sensor that combines a 3-axis 
    accelerometer and a 3-axis gyroscope, allowing it to track motion and 
    orientation in three-dimensional space.
*/

typedef struct{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;    
} Gyro_t;

class MPU6050 
{

private:
    i2c_inst_t* i2c;
    uint8_t sda;
    uint8_t scl;
    
    void port_config();
    void start_sensor();

public:
    MPU6050(i2c_inst_t* i2c, uint8_t sca, uint8_t scl);

    void getGyro(Gyro_t *gyro);

};