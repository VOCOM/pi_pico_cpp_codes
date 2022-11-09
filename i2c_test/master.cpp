#include <stdint.h>
#include "pico/stdlib.h"

#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/i2c.h"

#define UART_ID uart0
#define BAUD_RATE 115200

#define I2C_EXT_CHN i2c0

enum{
    I2C_ADD = 0xF0,
    I2C_SCL = 17,
    I2C_SDA = 16
};

int main(){

    stdio_init_all();
    sleep_ms(1000);
    printf("Begin\n");
    sleep_ms(1000);

    i2c_init(I2C_EXT_CHN, 10 * 1000);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);
    gpio_pull_up(I2C_SDA);

    uint8_t op{0xA0};
    uint8_t data[6]{0, 1, 2, 3, 4, 5};

    while(1){
        i2c_write_blocking(I2C_EXT_CHN, 0xFF, &op, 1, true);
        i2c_write_blocking(I2C_EXT_CHN, 0xFF, data, 6, false);
        printf("Written: %u, %u, %u, %u, %u, %u\n", data[0], data[1], data[2], data[3], data[4], data[5]);
        sleep_ms(1000);
        for(size_t i{}; i < 6; i++) data[i]++;
    }
}