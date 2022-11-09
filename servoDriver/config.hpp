//Debugging
#define UART_ID     uart0
#define BAUD_RATE   115200
//I2C
#define I2C_SLAVE_CHN   i2c0
#define MUX_I2C         i2c1

enum{
    //Servo Configurations
    AXIS_NUM = 6,

    //I2C Configurations
    I2C_ADD     = 0xFF,
    I2C_SCL     = 17,
    I2C_SDA     = 16,
    I2C_RATE    = 100 * 1000,

    //I2C OP Codes
    ERROR   = 0xAF,
    SETGOAL = 0xA0,
    GETPOS  = 0xA1,

    //Multiplexer Configurations
    MUX_ADD     = 0x70,
    MUX_SCL     = 19,
    MUX_SDA     = 18,
    MUX_RATE    = 100 * 1000
};