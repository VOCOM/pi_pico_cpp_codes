#include "servoDriver.hpp"
#include "TCA9548A.hpp"

#define I2C_EXT_CHN i2c0

enum{
    I2C_ADD = 0xFF,
    I2C_SCL = 24,
    I2C_SDA = 23,

    AXIS_NUM = 6
};

//Private Function Prototypes
void init();

int main(){

//Initialise I2C to external machine
init();

//Position Registers
uint8_t goal_position[AXIS_NUM]{};
uint8_t curr_position[AXIS_NUM]{};

//Multiplexer
TCA9548ADriver Mux;

//Servos
ServoDriver BASE_X(ServoDriver::SERVO1_PIN, curr_position + 0, goal_position + 0);
ServoDriver BASE_Z(ServoDriver::SERVO2_PIN, curr_position + 1, goal_position + 1);
ServoDriver ARM1_X(ServoDriver::SERVO3_PIN, curr_position + 2, goal_position + 2);
ServoDriver ARM1_Z(ServoDriver::SERVO4_PIN, curr_position + 3, goal_position + 3);
ServoDriver ARM2_X(ServoDriver::SERVO5_PIN, curr_position + 4, goal_position + 4);
ServoDriver ARM2_Z(ServoDriver::SERVO6_PIN, curr_position + 5, goal_position + 5);

//Update Loop
while(1){
    //Read Incoming Position
    for(uint8_t i{}; i < AXIS_NUM; i++){
        Mux.readPacket(i, goal_position+i, 1, 1000);
    }

    //Update Servo
    BASE_X.update();

    //Write Position to External Hardware
    for(uint8_t i{}; i < AXIS_NUM; i++){
        i2c_write_timeout_us(I2C_EXT_CHN, I2C_ADD, curr_position, 1, false, 100);
    }
}//while(1)

}//main

void init(){
    i2c_init(I2C_EXT_CHN, 100 * 1000);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);
    gpio_pull_up(I2C_SDA);
}