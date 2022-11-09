#include "servoDriver.hpp"
#include "TCA9548A.hpp"
//For Debug
#include <stdio.h>
#include "hardware/uart.h"
//Configurations file
#include "config.hpp"

void init();

int main(){
//OP Codes
uint8_t err_code{ERROR};
uint8_t op{};

    stdio_init_all();
    sleep_ms(1000);
    printf("Begin\n");
    sleep_ms(1000);

//Initialise I2C to external machine
init();

//Position Registers
uint8_t goal_position[AXIS_NUM]{};
uint8_t curr_position[AXIS_NUM]{};

//Multiplexer
TCA9548ADriver Mux(MUX_I2C, MUX_ADD, MUX_SCL, MUX_SDA, MUX_RATE);

//Servos
ServoDriver BASE_X(ServoDriver::SERVO1_PIN, curr_position + 0, goal_position + 0);
ServoDriver BASE_Z(ServoDriver::SERVO2_PIN, curr_position + 1, goal_position + 1);
ServoDriver ARM1_X(ServoDriver::SERVO3_PIN, curr_position + 2, goal_position + 2);
ServoDriver ARM1_Z(ServoDriver::SERVO4_PIN, curr_position + 3, goal_position + 3);
ServoDriver ARM2_X(ServoDriver::SERVO5_PIN, curr_position + 4, goal_position + 4);
ServoDriver ARM2_Z(ServoDriver::SERVO6_PIN, curr_position + 5, goal_position + 5);

//Update Loop
while(1){
    //Read Incoming Instruction
    if(i2c_get_read_available(I2C_SLAVE_CHN)){
        i2c_read_raw_blocking(I2C_SLAVE_CHN, &op, 1);
        printf("OP Code: %u\n", op);
        switch (op){
            //Read Incoming Positions
            case SETGOAL:
                i2c_read_raw_blocking(I2C_SLAVE_CHN, goal_position, AXIS_NUM);
                break;
            //Write Encoder Positions
            case GETPOS:
                i2c_write_raw_blocking(I2C_SLAVE_CHN, curr_position, AXIS_NUM);
                break;
            //Unkown Code Error
            default:
                i2c_write_raw_blocking(I2C_SLAVE_CHN, &err_code, 1);
                break;
        }
    }
    scanf("%d", goal_position);
    //Update Servo
    BASE_X.update();

    printf("goal: %d, %d, %d, %d, %d, %d\n", goal_position[0], goal_position[1], goal_position[2], goal_position[3], goal_position[4], goal_position[5]);
    printf("curr: %d, %d, %d, %d, %d, %d\n\n", curr_position[0], curr_position[1], curr_position[2], curr_position[3], curr_position[4], curr_position[5]);
    sleep_ms(250);
}//while(1)

}//main

/**
 * @brief Initialise I2C in Slave Mode
 */
void init(){
    i2c_init(I2C_SLAVE_CHN, I2C_RATE);
    i2c_set_slave_mode(I2C_SLAVE_CHN, true, I2C_ADD);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);
    gpio_pull_up(I2C_SDA);
}