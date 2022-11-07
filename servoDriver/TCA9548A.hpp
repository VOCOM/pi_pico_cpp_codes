#ifndef __TCA9548A__
#define __TCA9548A__

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_CHN i2c1

class TCA9548ADriver {
private:
int baudrate;

public:
enum{
    I2C_ADD = 0x70,
    I2C_SCL = 21,
    I2C_SDA = 20
};

TCA9548ADriver(){
    baudrate = i2c_init(I2C_CHN, 100 * 1000);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);
    gpio_pull_up(I2C_SDA);
}

/**
 * @brief Sends data to the Slave device
 * 
 * @param bus Slave channel
 * @param data Pointer to the source packet
 * @param len Number of bytes
 * @param timeout Timeout in us
 */
void sendPacket(char bus, uint8_t* data, int len, size_t timeout){
    //Select Slave Bus
    uint8_t channel = 1 << bus;
    i2c_write_timeout_us(I2C_CHN, I2C_ADD, &channel, 1, true, 100);
    //Send data to the selected bus
    i2c_write_timeout_us(I2C_CHN, I2C_ADD, data, len, false, timeout);
}

/**
 * @brief Reads data from Slave device
 * 
 * @param bus Slave channel
 * @param data Pointer to the destination
 * @param len Length of the incoming data
 * @param timeout Timeout in us
 */
void readPacket(char bus, uint8_t* data, int len, size_t timeout){
    //Select Slave Bus
    uint8_t channel = 1 << bus;
    i2c_write_timeout_us(I2C_CHN, I2C_ADD, &channel, 1, true, 100);
    //Read data from the selected bus
    i2c_read_timeout_us(I2C_CHN, I2C_ADD, data, len, false, timeout);
}

};

#endif