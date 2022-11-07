cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(motorDriver_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(driver
  driver.cpp
)

pico_enable_stdio_usb(driver 1)
pico_enable_stdio_uart(driver 1)

pico_add_extra_outputs(driver)

target_link_libraries(driver
  pico_stdlib			#Core Functionality
  pico_time				#Sleep_ms
  hardware_pwm			#PWM
  #pico_cyw43_arch_none	#Onboard LED connected to wifi module
)