#include "GPIO.h"
#include "BitOperationUtils.h"

void GpioSetup(tGpioPort * const port, uint8_t pin, tGpioMode mode, tGpioOutputType outputType, tGpioOutputSpeed outputSpeed, tGpioPull pull, uint8_t altFuncNum)
{
    /* TODO: generalize this */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

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

/* GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_1; */

    if (8U > pin)
    {
        BFM32(port->AFR[0],   PORTSETUP_QUADRUPLE_BITFIELD_ALL(pin), PORTSETUP_QUADRUPLE_BITFIELD_SET(pin, altFuncNum));
    }
    else
    {
        BFM32(port->AFR[1],   PORTSETUP_QUADRUPLE_BITFIELD_ALL((pin - 8U)), PORTSETUP_QUADRUPLE_BITFIELD_SET((pin - 8U), altFuncNum));
    }
}