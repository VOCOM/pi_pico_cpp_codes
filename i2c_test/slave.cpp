#include <stdint.h>
#include "pico/stdlib.h"

#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/i2c.h"

#define UART_ID uart0
#define BAUD_RATE 115200

#define I2C_EXT_CHN i2c0

enum{
    I2C_ADD = 0xFF,
    I2C_SCL = 17,
    I2C_SDA = 16
};

int main(){

    stdio_init_all();
    sleep_ms(1000);
    printf("Begin\n");
    sleep_ms(1000);

    i2c_init(I2C_EXT_CHN, 10 * 1000);
    i2c_set_slave_mode(I2C_EXT_CHN, true, I2C_ADD);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);
    gpio_pull_up(I2C_SDA);
    uint8_t data[6]{};
    uint8_t data_num{};

    while(1){
        i2c_read_raw_blocking(I2C_EXT_CHN, data, 1);
        printf("Value: %u, %u, %u, %u, %u, %u\n", data[0], data[1], data[2], data[3], data[4], data[5]);
        sleep_ms(1000);
    }
}