#include "servoDriver.hpp"
#include "TCA9548A.hpp"

int main(){
    ServoDriver::ServoList.push_back(new ServoDriver(SERVO1_PIN));
    ServoDriver::ServoList.push_back(new ServoDriver(SERVO2_PIN));
    ServoDriver::ServoList.push_back(new ServoDriver(SERVO3_PIN));
    ServoDriver::ServoList.push_back(new ServoDriver(SERVO4_PIN));
    ServoDriver::ServoList.push_back(new ServoDriver(SERVO5_PIN));
    ServoDriver::ServoList.push_back(new ServoDriver(SERVO6_PIN));

    // ServoDriver S1(SERVO16_PIN);
    
    // while(1){
    //     for(int a{}; a <= 90; a++){
    //         S1.setServo(a);
    //         sleep_ms(100);
    //     }
    //     sleep_ms(5000);

    //     for(int a{90}; a >= 0; a--){
    //         S1.setServo(a);
    //         sleep_ms(100);
    //     }
    //     sleep_ms(5000);
    // }
}