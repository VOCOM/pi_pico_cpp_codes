cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(servoDriver
    servoDriver.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(servoDriver
    pico_stdlib
    pico_time
    hardware_pwm
    hardware_i2c
    hardware_uart   #Debug
    pico_cyw43_arch_none
)

#For Debugging
pico_enable_stdio_usb(servoDriver 1)
pico_enable_stdio_uart(servoDriver 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(servoDriver)