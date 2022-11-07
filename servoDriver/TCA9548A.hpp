#include "pico/stdlib.h"
#include "hardware/i2c.h"

enum{
    I2C_ADD = 0b1110,
    I2C_SCL = 21,
    I2C_SDA = 20
};

class TCA9548A {
public:
TCA9548A(int pin1_, int pin2_, int pin3_){
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);
    gpio_pull_up(I2C_SDA);
}

/**
 * @brief Sends data to the TCA9548A
 * 
 * @param device Slave address 0 - 7
 * @param RW True = Write / False = Read
 * @param data_ptr Pointer to the data packet
 * @param len Number of bytes
 */
void sendPacket(int device, int RW, int* data_ptr, int len){
    int start = 0b11100000 | device;
    int stop = 
}

private:
};