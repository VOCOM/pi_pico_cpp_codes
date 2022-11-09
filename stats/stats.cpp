#include "pico/stdlib.h"
#include "hardware/adc.h"

#include <stdio.h>
#include "hardware/uart.h"

#include <stdint.h>

int main(){
    stdio_init_all();
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);
    double temp{}, val{};

    while(1){
        val = adc_read();
        temp = 27 - ((val * (3.3 / (1<<12))) - 0.706)/0.001721;
        printf("Raw: %.2lf Voltage: %.2lf Onboard Temperature: %.2lf\n", val, val * (3.3 / (1<<12)), temp);
        sleep_ms(1000);
    }
}