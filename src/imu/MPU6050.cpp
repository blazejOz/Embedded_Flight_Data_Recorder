#include "MPU6050.h"

MPU6050::MPU6050(i2c_inst_t *i2c, uint8_t sda, uint8_t scl)
{ 
    this->i2c = i2c;
    this->sda = sda;
    this->scl = scl;

    port_config();
    start_sensor();
}

void MPU6050::port_config()
{
    stdio_init_all();

    i2c_init(i2c, 400 * 1000);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(scl);

}

void MPU6050::start_sensor()
{
    uint8_t reset[] = {REG_PWR_MGMT_1, 0x80};
    i2c_write_blocking(i2c, MPU6050_ADDR, reset, 2, false);

    sleep_ms(200);

    uint8_t wake[] = {REG_PWR_MGMT_1, 0x00};
    i2c_write_blocking(i2c, MPU6050_ADDR, wake, 2, false);

    sleep_ms(200);

    uint8_t who_am_i = 0;
    uint8_t reg = REG_WHO_AM_I;

    i2c_write_blocking(i2c, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c, MPU6050_ADDR, &who_am_i, 1, false);

    sleep_ms(600);

    printf("MPU6050 WHO_AM_I: %hhu\n", who_am_i);

    sleep_ms(600);
    
    if (who_am_i != WHO_AM_I_VALUE) {
        while (true) {
            printf("MPU6050 not found!\n");
            sleep_ms(1000);
        }
    }

}