#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"

class MotorDriver {
public:
enum
{
    EN1 = 0,
    EN2,
    EN3,
    EN4,
    M1A,
    M1B,
    M2A,
    M2B,
    M3A,
    M3B,
    M4A,
    M4B,

    CW,
    CCW
};
typedef unsigned int uint;

MotorDriver();
void setMotor(int motorPin, int dir, int val);
void Move(uint r, uint theta);

private:
int pos_;
};

MotorDriver::MotorDriver(){
    //PWM Pins, left verbose for custom pin allocation
    gpio_set_function(EN1, GPIO_FUNC_PWM);
    gpio_set_function(EN2, GPIO_FUNC_PWM);
    gpio_set_function(EN3, GPIO_FUNC_PWM);
    gpio_set_function(EN4, GPIO_FUNC_PWM);
    //Configure PWM
    pwm_config config = pwm_get_default_config();
    pwm_init(pwm_gpio_to_slice_num(EN1), &config, true);
    pwm_init(pwm_gpio_to_slice_num(EN2), &config, true);
    pwm_init(pwm_gpio_to_slice_num(EN3), &config, true);
    pwm_init(pwm_gpio_to_slice_num(EN4), &config, true);
    //Direction Pins, left verbose for custom pin allocation
    gpio_init(M1A);
    gpio_init(M1B);
    gpio_init(M2A);
    gpio_init(M2B);
    gpio_init(M3A);
    gpio_init(M3B);
    gpio_init(M4A);
    gpio_init(M4B);
}

void MotorDriver::setMotor(int motorPin, int dir, int val){
    int pinA, pinB;

    switch (motorPin){
    case EN1:
        pinA = M1A;
        pinB = M1B;
        break;
    case EN2:
        pinA = M2A;
        pinB = M2B;
        break;
    case EN3:
        pinA = M3A;
        pinB = M3B;
        break;
    case EN4:
        pinA = M4A;
        pinB = M4B;
        break;
    default:
        break;
    }

    if(dir == CW){
        gpio_set_dir(pinA, true);
        gpio_set_dir(pinB, false);
    }else{
        gpio_set_dir(pinA, false);
        gpio_set_dir(pinB, true);
    }
    pwm_set_gpio_level(motorPin, val);
}

void MotorDriver::Move(uint r, uint theta){
    theta %= 360;
    if(theta >= 45 && theta < 135){         //Quadrant 1
        theta -= 45;
        setMotor(EN1, CW, r*sin(theta));
        setMotor(EN2, CW, r*cos(theta));
        setMotor(EN3, CW, r*cos(theta));
        setMotor(EN4, CW, r*sin(theta));
    }else if(theta >= 135 && theta < 225){  //Quadrant 2
        theta -= 135;
        setMotor(EN1, CW , r*cos(theta));
        setMotor(EN2, CCW, r*sin(theta));
        setMotor(EN3, CCW, r*sin(theta));
        setMotor(EN4, CW , r*cos(theta));
    }else if(theta >= 225 && theta < 315){  //Quadrant 3
        theta -= 225;
        setMotor(EN1, CCW, r*sin(theta));
        setMotor(EN2, CCW, r*cos(theta));
        setMotor(EN3, CCW, r*cos(theta));
        setMotor(EN4, CCW, r*sin(theta));
    }else{                                  //Quadrant 4
        theta = theta < 45 ? theta + 45 : theta - 315;
        setMotor(EN1, CCW, r*cos(theta));
        setMotor(EN2, CW , r*sin(theta));
        setMotor(EN3, CW , r*sin(theta));
        setMotor(EN4, CCW, r*cos(theta));
    }
}

/*
void MotorDriver::Move(uint r, uint theta){
    theta %= 360;
    if(theta >= 45 && theta < 135){         //Quadrant 1
        theta -= 45;
        pwm_set_both_levels(2, r*sin(theta), 0);
        pwm_set_both_levels(3, r*cos(theta), 0);
        pwm_set_both_levels(4, r*cos(theta), 0);
        pwm_set_both_levels(5, r*sin(theta), 0);
    }else if(theta >= 135 && theta < 225){  //Quadrant 2
        theta -= 135;
        pwm_set_both_levels(2, r*cos(theta), 0);
        pwm_set_both_levels(3, 0, r*sin(theta));
        pwm_set_both_levels(4, 0, r*sin(theta));
        pwm_set_both_levels(5, r*cos(theta), 0);
    }else if(theta >= 225 && theta < 315){  //Quadrant 3
        theta -= 225;
        pwm_set_both_levels(2, 0, r*sin(theta));
        pwm_set_both_levels(3, 0, r*cos(theta));
        pwm_set_both_levels(4, 0, r*cos(theta));
        pwm_set_both_levels(5, 0, r*sin(theta));
    }else{                                  //Quadrant 4
        theta = theta < 45 ? theta + 45 : theta - 315;
        pwm_set_both_levels(2, 0, r*cos(theta));
        pwm_set_both_levels(3, r*sin(theta), 0);
        pwm_set_both_levels(4, r*sin(theta), 0);
        pwm_set_both_levels(5, 0, r*cos(theta));
    }
}
*/