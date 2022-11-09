#ifndef __TCA9548A__
#define __TCA9548A__

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class TCA9548ADriver {
private:
uint8_t I2C_ADD;
uint8_t I2C_SCL;
uint8_t I2C_SDA;
unsigned int baudrate;
i2c_inst_t* channel;

public:
/**
 * @brief Construct a new TCA9548ADriver object
 * 
 * @param channel Either i2c0 or i2c1
 * @param add Address of the TCA9548A
 * @param scl SCL Pin
 * @param sda SDA Pin
 * @param baud Baudrate in Hz
 */
TCA9548ADriver(i2c_inst_t* channel, uint8_t add, uint8_t scl, uint8_t sda, unsigned int baud):
    I2C_ADD(add), I2C_SCL(scl), I2C_SDA(sda), baudrate(baud), channel(channel){
        baudrate = i2c_init(channel, baudrate);
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
void sendPacket(uint8_t bus, uint8_t* data, int len, size_t timeout){
    //Select Slave Bus
    bus = 1 << bus;
    i2c_write_timeout_us(channel, I2C_ADD, &bus, 1, true, 100);
    //Send data to the selected bus
    i2c_write_timeout_us(channel, I2C_ADD, data, len, false, timeout);
}

/**
 * @brief Reads data from Slave device
 * 
 * @param bus Slave channel
 * @param data Pointer to the destination
 * @param len Length of the incoming data
 * @param timeout Timeout in us
 */
void readPacket(uint8_t bus, uint8_t* data, int len, size_t timeout){
    //Select Slave Bus
    bus = 1 << bus;
    i2c_write_timeout_us(channel, I2C_ADD, &bus, 1, true, 100);
    //Read data from the selected bus
    i2c_read_timeout_us(channel, I2C_ADD, data, len, false, timeout);
}

};

#endif