#ifndef GPIO_H
#define GPIO_H


#include "stm32g431xx.h"

#define PROJDEF_SYSCLK_FREQ_HZ      (16000000u)
#define PROJCFG_AHBPRESC        (1u)
#define PROJCFG_APB1PRESC       (1u)
#define PROJCFG_APB2PRESC       (1u)



#define PROJDEF_HCLK_FREQ_HZ  (PROJDEF_SYSCLK_FREQ_HZ / PROJCFG_AHBPRESC)
#define PROJDEF_PCLK1_FREQ_HZ (PROJDEF_HCLK_FREQ_HZ / PROJCFG_APB1PRESC)
#define PROJDEF_PCLK2_FREQ_HZ (PROJDEF_HCLK_FREQ_HZ / PROJCFG_APB2PRESC)

#define PROJDEF_APB1_TIM_FREQ_HZ (PROJDEF_PCLK1_FREQ_HZ * ((PROJCFG_APB1PRESC == 1u) ? (1u) : (2u)))
#define PROJDEF_APB2_TIM_FREQ_HZ (PROJDEF_PCLK2_FREQ_HZ * ((PROJCFG_APB2PRESC == 1u) ? (1u) : (2u)))

/* For setting TIM 2..5 prescale register to a desired frequency */
#define APB1_TIM_PRESC_SET(desiredFreq)  ((uint16_t)((PROJDEF_APB1_TIM_FREQ_HZ / (desiredFreq)) - 1U))

/*********************/
/**** GPIO MACROS ****/
/*********************/

#define GPIO_SET(port, pin)              ((port)->BSRR |= 0x1U << (pin))
#define GPIO_RESET(port, pin)            ((port)->BRR  |= 0x1U << (pin))
#define GPIO_TOGGLE(port, pin)           ((port)->ODR  ^= 0x1U << (pin))

#define GPIO_SETUP_MODE(port, pin, mode) ((port)->MODER = ((port)->MODER & (uint32_t)(~(3U << (2U * (pin))))) | (uint32_t)((mode) << (2U * (pin))))


#define PORTSETUP_SINGLE_BITFIELD_ALL(pin)          ((uint32_t)(0x1U << (1U * (pin))))
#define PORTSETUP_DOUBLE_BITFIELD_ALL(pin)          ((uint32_t)(0x3U << (2U * (pin))))
#define PORTSETUP_QUADRUPLE_BITFIELD_ALL(pin)       ((uint32_t)(0x15U << (4U * (pin))))
#define PORTSETUP_SINGLE_BITFIELD_SET(pin, bits)    ((uint32_t)((bits) << (1U * (pin))))
#define PORTSETUP_DOUBLE_BITFIELD_SET(pin, bits)    ((uint32_t)((bits) << (2U * (pin))))
#define PORTSETUP_QUADRUPLE_BITFIELD_SET(pin, bits) ((uint32_t)((bits) << (4U * (pin))))

/*********************/
/**** GPIO MACROS ****/
/*********************/

/**
 * @brief GPIO port.
 */
typedef GPIO_TypeDef tGpioPort;

/**
 * @brief GPIO pin.
 */
typedef enum
{
    /** Pin 0 */
    GPIO_PIN0,

    /** Pin 1 */
    GPIO_PIN1,

    /** Pin 2 */
    GPIO_PIN2,

    /** Pin 3 */
    GPIO_PIN3,

    /** Pin 4 */
    GPIO_PIN4,

    /** Pin 5 */
    GPIO_PIN5,

    /** Pin 6 */
    GPIO_PIN6,

    /** Pin 7 */
    GPIO_PIN7,

    /** Pin 8 */
    GPIO_PIN8,

    /** Pin 9 */
    GPIO_PIN9,

    /** Pin 10 */
    GPIO_PIN10,

    /** Pin 11 */
    GPIO_PIN11,

    /** Pin 12 */
    GPIO_PIN12,

    /** Pin 13 */
    GPIO_PIN13,

    /** Pin 14 */
    GPIO_PIN14,

    /** Pin 15 */
    GPIO_PIN15

} tGpioPin;

/**
 * @brief GPIO modes.
 */
typedef enum
{
    /** Input. */
    GPIO_INPUT = 0U,

    /** General purpose output. */
    GPIO_OUTPUT,

    /** Alternate function. */
    GPIO_ALT_FUNC,

    /** Analog. */
    GPIO_ANALOG

} tGpioMode;

/**
 * @brief GPIO output types.
 */
typedef enum
{
    /** Default */
    GPIO_DEFAULT = 0U,

    /** Push-pull. */
    GPIO_PUSH_PULL = 0U,

    /** Open-drain. */
    GPIO_OPEN_DRAIN

} tGpioOutputType;

/**
 * @brief GPIO output speeds.
 */
typedef enum
{
    /** Low. */
    GPIO_LOW = 0U,

    /** Medium. */
    GPIO_MEDIUM,

    /** High. */
    GPIO_HIGH,

    /** Very High. */
    GPIO_VERY_HIGH

} tGpioOutputSpeed;

/**
 * @brief GPIO pull-up / pull-down modes.
 */
typedef enum
{
    /** No pull. */
    GPIO_DISABLED = 0U,

    /** Pull up. */
    GPIO_UP,

    /** Pull down. */
    GPIO_DOWN

} tGpioPull;


void GpioSetup(tGpioPort * const port, uint8_t pin, tGpioMode mode, tGpioOutputType outputType, tGpioOutputSpeed outputSpeed, tGpioPull pull, uint8_t altFuncNum);


#endif /* GPIO_H */
