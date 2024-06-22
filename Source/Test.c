#include "stm32g431xx.h"
#include "Test.h"
#include "BitOperationUtils.h"



void Test_Blank(void)
{
    while (1U)
    {

    }
}



void Test_GPIO_Toggle_1(void)
{

    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN8;
    tGpioMode        mode        = GPIO_OUTPUT;
    tGpioOutputType  outputType  = GPIO_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_LOW;
    tGpioPull        pull        = GPIO_DEFAULT;
    uint8_t          altFuncNum  = 0U;

    GpioSetup(port, pin, mode, outputType, outputSpeed, pull, altFuncNum);

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



void Test_GPIO_Toggle_2(void)
{

    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN8;
    tGpioMode        mode        = GPIO_OUTPUT;
    tGpioOutputType  outputType  = GPIO_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_LOW;
    tGpioPull        pull        = GPIO_DEFAULT;
    uint8_t          altFuncNum  = 0U;

    GpioSetup(port, pin, mode, outputType, outputSpeed, pull, altFuncNum);


    while(1)
    {
        volatile uint32_t i;

        GPIO_TOGGLE(port, pin);

        for(i = 0u; i < 1000000u; i++)
        {
        }

        GPIO_TOGGLE(port, pin);

        for(i = 0u; i < 1000000u; i++)
        {
        }
    }
}



void Test_Timer_1(void)
{
    volatile uint32_t counter;

    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN8;
    tGpioMode        mode        = GPIO_OUTPUT;
    tGpioOutputType  outputType  = GPIO_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_LOW;
    tGpioPull        pull        = GPIO_DEFAULT;
    uint8_t          altFuncNum  = 0U;

    GpioSetup(port, pin, mode, outputType, outputSpeed, pull, altFuncNum);

    /* Enable TIM3 timer clock */
    BFS32(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);

    /* Set auto relode register */
    TIM3->ARR = (uint32_t)1000U;

    /* Set prescale register */
    TIM3->PSC = APB1_TIM_PRESC_SET(1000U);

    /* Enable timer */
    BFS32(TIM3->CR1, TIM_CR1_CEN);

    while (1U)
    {
        /* Value of the timer counter */
        counter = TIM3->CNT;

        /* When the update interrupt flag is set */
        if (TIM_SR_UIF == (TIM3->SR & TIM_SR_UIF_Msk))
        {
            /* Toggle LED pin */
            GPIO_TOGGLE(port, pin);

            /* Clear update interrupt flag */
            BFC32(TIM3->SR, TIM_SR_UIF);
        }
    }
}



void TIM3_IRQHandler(void)
{
    /* Global variable? */
    tGpioPort * port = GPIOB;
    tGpioPin    pin  = GPIO_PIN8;

    /* Toggle LED pin */
    GPIO_TOGGLE(port, pin);

    /* Reset update interrupt flag */
    /* NOTE: There are more interrupt flags, and it is must be reseted otherwise the interrupt is not
     * set again */
    BFC32(TIM3->SR, TIM_SR_UIF);
}



void Test_Timer_2(void)
{
    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN8;
    tGpioMode        mode        = GPIO_OUTPUT;
    tGpioOutputType  outputType  = GPIO_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_LOW;
    tGpioPull        pull        = GPIO_DEFAULT;
    uint8_t          altFuncNum  = 0U;

    /* Setup builtin led output */
    GpioSetup(port, pin, mode, outputType, outputSpeed, pull, altFuncNum);

    /* Enable TIM3 timer clock */
    BFS32(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);

    /* Set auto relode register */
    TIM3->ARR = (uint32_t)1000U;

    /* Set prescale register */
    TIM3->PSC = APB1_TIM_PRESC_SET(1000U);

    /* Enable the TIM3 interrupt */
    NVIC_EnableIRQ(TIM3_IRQn);

    /* Set TIM3 interrupt priority */
    NVIC_SetPriority(TIM3_IRQn, 0U);

    /* Enable update interrupt event */
    BFS32(TIM3->DIER, TIM_DIER_UIE);

    /* Enable timer */
    BFS32(TIM3->CR1, TIM_CR1_CEN);

    while (1U)
    {
    }
}



void Test_PWM_1(void)
{
    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN8;
    tGpioMode        mode        = GPIO_ALT_FUNC;
    tGpioOutputType  outputType  = GPIO_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_LOW;
    tGpioPull        pull        = GPIO_DEFAULT;
    uint8_t          altFuncNum  = 2U;

    /* Setup builtin led output with alternate function (CH3) */
    GpioSetup(port, pin, mode, outputType, outputSpeed, pull, altFuncNum);

    /* Enable TIM4 timer clock */
    BFS32(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN);

    /* Set prescale register (1MHz) */
    TIM4->PSC = APB1_TIM_PRESC_SET(1000000U);

    /* Set auto relode register (1KHz) */
    TIM4->ARR = (uint32_t)999U;

    /* Set compare value for duty cycle */
    TIM4->CCR3 = 0U;

    /* Set PWM mode 1 on chanel 3 */
    BFM32(TIM4->CCMR2, TIM_CCMR2_OC3M_Msk, (TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2));

    /* Set preload enable register of chanel 3 */
    BFS32(TIM4->CCMR2, TIM_CCMR2_OC3PE);

    /* Set auto-reload register */
    BFS32(TIM4->CR1, TIM_CR1_ARPE);

    /* Update registers */
    /* TIM4->EGR |= TIM_EGR_UG; */

    /* Set timer capture/compare enable register of chanel 3 */
    BFS32(TIM4->CCER, TIM_CCER_CC3E);

    /* Enable timer */
    BFS32(TIM4->CR1, TIM_CR1_CEN);

    uint8_t counter = 0U;

    while(1U)
    {
        uint32_t i;

        /* Wait some time */
        for(i = 0U; i < 10000U; i++)
        {
        }

        /* Update duty cycle */
        TIM4->CCR3 = (uint32_t)(counter++);

        /* Reset duty cycle */
        if (200U <= counter)
        {
            counter = 0U;
        }
    }
}