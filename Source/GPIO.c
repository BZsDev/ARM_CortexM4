#include "GPIO.h"
#include "BitOperationUtils.h"

void GpioSetup(tGpioPort * const port, uint8_t pin, tGpioMode mode, tGpioOutputType outputType, tGpioOutputSpeed outputSpeed, tGpioPull pull, uint8_t altFuncNum)
{
    if      (GPIOA == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    else if (GPIOB == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    else if (GPIOC == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    else if (GPIOD == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
    else if (GPIOE == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
    else if (GPIOF == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOFEN;
    else if (GPIOG == port) RCC->AHB2ENR |= RCC_AHB2ENR_GPIOGEN;


/*     port->MODER &= (uint32_t)~(0x3UL << (2u * pin));
    port->MODER |= (uint32_t)(mode << (2u * pin));

    port->OTYPER &= (uint32_t)~(0x1UL << (1u * pin));
    port->OTYPER |= (uint32_t)(outputType << (1u * pin));

    port->OSPEEDR &= (uint32_t)~(0x3UL << (2u * pin));
    port->OSPEEDR |= (uint32_t)(outputSpeed << (2u * pin));

    port->PUPDR &= (uint32_t)~(0x3UL << (2u * pin));
    port->PUPDR |= (uint32_t)(pull << (2u * pin));

    port->PUPDR &= (uint32_t)~(0x3UL << (2u * pin));
    port->PUPDR |= (uint32_t)(pull << (2u * pin)); */



    BFM32(port->MODER,   PORTSETUP_DOUBLE_BITFIELD_ALL(pin), PORTSETUP_DOUBLE_BITFIELD_SET(pin, mode));
    BFM32(port->OTYPER,  PORTSETUP_SINGLE_BITFIELD_ALL(pin), PORTSETUP_SINGLE_BITFIELD_SET(pin, outputType));
    BFM32(port->OSPEEDR, PORTSETUP_DOUBLE_BITFIELD_ALL(pin), PORTSETUP_DOUBLE_BITFIELD_SET(pin, outputSpeed));
    BFM32(port->PUPDR,   PORTSETUP_DOUBLE_BITFIELD_ALL(pin), PORTSETUP_DOUBLE_BITFIELD_SET(pin, pull));


    if (8U > pin)
    {
        BFM32(port->AFR[0],   PORTSETUP_QUADRUPLE_BITFIELD_ALL(pin), PORTSETUP_QUADRUPLE_BITFIELD_SET(pin, altFuncNum));
    }
    else
    {
        BFM32(port->AFR[1],   PORTSETUP_QUADRUPLE_BITFIELD_ALL((pin - 8U)), PORTSETUP_QUADRUPLE_BITFIELD_SET((pin - 8U), altFuncNum));
    }
}