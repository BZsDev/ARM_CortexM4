#include "stm32g431xx.h"
#include "Test.h"
#include "BitOperationUtils.h"



void Test_Blank(void)
{
    while (1U)
    {

    }
}



void Test_GPIO_Out_Toggle_1(void)
{

    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN_8;
    tGpioMode        mode        = GPIO_MODE_OUTPUT;
    tGpioOutputType  outputType  = GPIO_OTYPE_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_OSPEED_LOW;
    tGpioPull        pull        = GPIO_PULL_DISABLED;
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



void Test_GPIO_Out_Toggle_2(void)
{

    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN_8;
    tGpioMode        mode        = GPIO_MODE_OUTPUT;
    tGpioOutputType  outputType  = GPIO_OTYPE_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_OSPEED_LOW;
    tGpioPull        pull        = GPIO_PULL_DISABLED;
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
    tGpioPin         pin         = GPIO_PIN_8;
    tGpioMode        mode        = GPIO_MODE_OUTPUT;
    tGpioOutputType  outputType  = GPIO_OTYPE_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_OSPEED_LOW;
    tGpioPull        pull        = GPIO_PULL_DISABLED;
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
    tGpioPin    pin  = GPIO_PIN_8;

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
    tGpioPin         pin         = GPIO_PIN_8;
    tGpioMode        mode        = GPIO_MODE_OUTPUT;
    tGpioOutputType  outputType  = GPIO_OTYPE_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_OSPEED_LOW;
    tGpioPull        pull        = GPIO_PULL_DISABLED;
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
    uint8_t counter = 0U;

    tGpioPort *      port        = GPIOB;
    tGpioPin         pin         = GPIO_PIN_8;
    tGpioMode        mode        = GPIO_MODE_ALT_FUNC;
    tGpioOutputType  outputType  = GPIO_OTYPE_PUSH_PULL;
    tGpioOutputSpeed outputSpeed = GPIO_OSPEED_LOW;
    tGpioPull        pull        = GPIO_PULL_DISABLED;
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

    while (1U)
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



void Test_GPIO_DigitalRead_1(void)
{
    tGpioPort * ledPort        = GPIOB;
    tGpioPin    ledPin         = GPIO_PIN_8;
    tGpioPort * buttonPort     = GPIOA;
    tGpioPin    buttonPin      = GPIO_PIN_2;

    /* Setup builtin LED output */
    GpioSetup(ledPort, ledPin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_LOW, GPIO_PULL_DISABLED, (uint8_t)0U);

    /* Setup PA2 input buttom */
    GpioSetup(buttonPort, buttonPin, GPIO_MODE_INPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_LOW, GPIO_PULL_DISABLED, (uint8_t)0U);

    while (1U)
    {
        /* If the input data register is set */
        if (TRUE == GPIO_DIGITAL_READ(buttonPort, buttonPin))
        {
            /* Set LED */
            GPIO_SET(ledPort, ledPin);
        }
        else
        {
            /* Reset LED */
            GPIO_RESET(ledPort, ledPin);
        }
    }
}



void Test_ADC_Single_1(void)
{
    uint16_t dataADC = 0U;
    uint16_t i;

    tGpioPort * analogPort     = GPIOB;
    tGpioPin    analogPin      = GPIO_PIN_0;

    /* Setup analog input GPIO */
    GpioSetup(analogPort, analogPin, GPIO_MODE_ANALOG, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_LOW, GPIO_PULL_DISABLED, (uint8_t)0U);

    /* Enable ADC1 clock */
    BFS32(RCC->AHB2ENR, RCC_AHB2ENR_ADC12EN);

    /* Exit deep power down mode */
    BFC32(ADC1->CR, ADC_CR_DEEPPWD);

    /* Enable ADC voltage regulator */
    BFS32(ADC1->CR, ADC_CR_ADVREGEN);

    /* Wait some time (datasheet needed for the exact time) */
    for (i = 0U; i < 1000U; i++);

    /* Calibrate ADC (ADEN must be 0) */
    BFS32(ADC1->CR, ADC_CR_ADCAL);

    /* Wait for calibration */
    while (ADC1->CR & ADC_CR_ADCAL_Msk);

    /* Enable ADC1 */
    BFS32(ADC1->CR, ADC_CR_ADEN);

    /* Wait until the ADC1 is ready */
    while (!(ADC1->ISR & ADC_ISR_ADRDY));

    /* Select chanel 15 for PB0 */
    BFM32(ADC1->SQR1, ADC_SQR1_SQ1_Msk, (15U << ADC_SQR1_SQ1_Pos));

    /* Set sample time */
    BFM32(ADC1->SMPR1, ADC_SMPR1_SMP1_Msk, (3U << ADC_SMPR1_SMP1_Pos));

    while (1U)
    {
        BFS32(ADC1->CR, ADC_CR_ADSTART);

        while (!(ADC1->ISR & ADC_ISR_EOC));

        dataADC = (uint16_t)(ADC1->DR);
    }

}