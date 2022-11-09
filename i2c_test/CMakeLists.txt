cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(master
master.cpp
)
add_executable(slave
slave.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(master
    pico_stdlib
    pico_time
    hardware_i2c
    hardware_uart   #Debug
)
target_link_libraries(slave
    pico_stdlib
    pico_time
    hardware_i2c
    hardware_uart   #Debug
)

#For Debugging
pico_enable_stdio_usb(master 1)
pico_enable_stdio_uart(master 0)
pico_enable_stdio_usb(slave 1)
pico_enable_stdio_uart(slave 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(master)
pico_add_extra_outputs(slave)