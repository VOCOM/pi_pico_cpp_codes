#ifndef __SERVO_DRIVER__
#define __SERVO_DRIVER__

#include <vector>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

class ServoDriver {
private:
int pin_;
uint8_t* cur_pos;
const uint8_t* goal_pos;

public:
enum{
    //I2C
    I2C_ADD = 0x36,

    //Clock configurations
    PWM_PRESCALER = 64,
    ARR = 39062,

    //Servo Pin Allocations
    SERVO1_PIN = 0,
    SERVO2_PIN,
    SERVO3_PIN,
    SERVO4_PIN,
    SERVO5_PIN,
    SERVO6_PIN,
    SERVO7_PIN,
    SERVO8_PIN,
    SERVO9_PIN,
    SERVO10_PIN,
    SERVO11_PIN,
    SERVO12_PIN,
    SERVO13_PIN,
    SERVO14_PIN,
    SERVO15_PIN,
    SERVO16_PIN,
    
    //Angle limits in micro seconds
    MINANGLE_us = 400,
    MAXANGLE_us = 2600,
    //Angle limits
    MINANGLE = 0,
    MAXANGLE = 198
};

ServoDriver(int pin, uint8_t* currPtr, const uint8_t* goalPtr): pin_(pin), cur_pos(currPtr), goal_pos(goalPtr){
    //Initialise GPIO & set Prescaler with auto reload register (ARR)
    gpio_set_function(pin, GPIO_FUNC_PWM);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, PWM_PRESCALER);
    pwm_config_set_wrap(&config, ARR);
    pwm_init(pwm_gpio_to_slice_num(pin_), &config, true);
}

/**
 * @brief Set the angle of the Servo
 * 
 * @param angle Angle in degree
 */
void setServo(int angle){
    if(angle < MINANGLE) return;
    if (angle > MAXANGLE) return;
    int angle_us = angle * (MAXANGLE_us - MINANGLE_us) / MAXANGLE + MINANGLE_us;
    pwm_set_gpio_level(pin_, angle_us / 20000.0 * ARR);
}

void readEncoder(){
    cur_pos = 0;
}

/**
 * @brief Sets and reads the servo
 * 
 */
void update(){
    setServo(*goal_pos);
    readEncoder();
}

};

#endif