#include "driver.hpp"

/*
uint pwm_slice[8]{};

void init(){
    stdio_init_all();
    for(unsigned char i{}; i < 8; i++){
        gpio_set_function(M1A + i, GPIO_FUNC_PWM);
        pwm_set_gpio_level(M1A + i, 0);
        if(i%2){
            pwm_set_wrap(i/2 + 2 , DUTYCYCLE_MAX);
            pwm_set_enabled(i/2 + 2,true);
        }
    }
}

void forward(uint spd){
    for(uint i{}; i < 4; i++){
        pwm_set_both_levels(2 + i, spd, 0);
    }
}

void reverse(uint spd){
    for(uint i{}; i < 4; i++){
        pwm_set_both_levels(2 + i, 0, spd);
    }
}

void left(uint spd){
    pwm_set_both_levels(2, spd, 0);
    pwm_set_both_levels(3, 0, spd);
    pwm_set_both_levels(4, 0, spd);
    pwm_set_both_levels(5, spd, 0);
}

void right(uint spd){
    pwm_set_both_levels(2, 0, spd);
    pwm_set_both_levels(3, spd, 0);
    pwm_set_both_levels(4, spd, 0);
    pwm_set_both_levels(5, 0, spd);
}

void stop(){
    for(uint i{}; i < 4; i++){
        pwm_set_both_levels(2 + i, 0, 0);
    }
}
*/

int main(){
    MotorDriver M1;

    while(true){
        M1.Move(50, 0);
        sleep_ms(2000);
        M1.Move(50, 90);
        sleep_ms(2000);
        M1.Move(50, 180);
        sleep_ms(2000);
        M1.Move(50, 270);
        sleep_ms(2000);
    }
}