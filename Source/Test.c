#include "stm32g431xx.h"
#include "Test.h"

void Test_GPIO_Toggle(void)
{

    tGpioPort * port = GPIOB;
    tGpioPin pin = GPIO_PIN8;
    tGpioMode mode = GPIO_OUTPUT;
    tGpioOutputType outputType = GPIO_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_LOW;
    tGpioPull pull = GPIO_DISABLED;
    uint8_t altFuncNum;

    GpioSetup(port, pin, 3U, outputType, outputSpeed, pull, altFuncNum);

    GPIO_SETUP_MODE(port, pin, mode);

    while(1)
    {
        volatile uint32_t i;

        GPIO_SET(port, pin);

        for(i = 0u; i < 1000000u; i++)
        {
        }

        GPIO_RESET(port, pin);

        for(i = 0u; i < 1000000u; i++)
        {
        }
    }
}