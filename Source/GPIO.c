#include "GPIO.h"

void GpioSetup(tGpioPort * const port, uint8_t pin, tGpioMode mode, tGpioOutputType outputType, tGpioOutputSpeed outputSpeed, tGpioPull pull, uint8_t altFuncNum)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    port->MODER &= (uint32_t)~(0x3UL << (2u * pin));
    port->MODER |= (uint32_t)(mode << (2u * pin));

    port->OTYPER &= (uint32_t)~(0x1UL << (1u * pin));
    port->OTYPER |= (uint32_t)(outputType << (1u * pin));

    port->OSPEEDR &= (uint32_t)~(0x3UL << (2u * pin));
    port->OSPEEDR |= (uint32_t)(outputSpeed << (2u * pin));

    port->PUPDR &= (uint32_t)~(0x3UL << (2u * pin));
    port->PUPDR |= (uint32_t)(pull << (2u * pin));

    port->PUPDR &= (uint32_t)~(0x3UL << (2u * pin));
    port->PUPDR |= (uint32_t)(pull << (2u * pin));
    
}