#include <vector>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

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

class ServoDriver {
public:
static std::vector<ServoDriver*> ServoList;
static void update(){

}
ServoDriver(int pin): pin_(pin){
    //Initialise GPIO & set Prescaler with auto reload register (ARR)
    gpio_set_function(pin, GPIO_FUNC_PWM);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, PWM_PRESCALER);
    pwm_config_set_wrap(&config, ARR);
    pwm_init(pwm_gpio_to_slice_num, &config, true);
}
void setServo(int angle){
    if(angle < MINANGLE) return;
    if (angle > MAXANGLE) return;
    int angle_us = angle * (MAXANGLE_us - MINANGLE_us) / MAXANGLE + MINANGLE_us;
    pwm_set_gpio_level(pin_, angle_us / 20000.0 * ARR);
}

int readEncoder(){

}

private:
int pin_;
int cur_pos;
int goal_pos;
};

std::vector<ServoDriver*> ServoDriver::ServoList{};