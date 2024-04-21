/* #include <stdio.h> */
#include <stdint.h>
#include "header.h"
#include "stm32g4xx.h"


#define MACRO_0 3u

uint8_t ledState = 0u;

void TIM2_IRQHandler(void) 
{

    TIM2->SR &= ~TIM_SR_UIF;
}

void TIM3_IRQHandler(void)
{
    if ((TIM3->SR & TIM_SR_CC1IF) != 0)
    {
        if (0u == ledState)
        {
            ledState = 1u;
            GPIOB->BSRR = GPIO_BSRR_BS8;
        }
        else
        {
            ledState = 0u;
            GPIOB->BRR = GPIO_BRR_BR8;
        }
        TIM3->SR &= ~TIM_SR_CC1IF;
    }
}

int main(void)
{
    uint32_t timerCntr;
    volatile uint32_t asd = SystemCoreClock;

    SystemCoreClockUpdate(); 
    
    /* printf("Hello %d", MACRO_0); */

    RCC->AHB2ENR |= (uint32_t)RCC_AHB2ENR_GPIOBEN;
    GPIOB->MODER &= (uint32_t)~GPIO_MODER_MODE8;
    GPIOB->MODER |= (uint32_t)(0x1U << GPIO_MODER_MODE8_Pos);

    /*
    GPIOB->MODER &= (uint32_t)~GPIO_MODER_MODE5;
    GPIOB->PUPDR &= (uint32_t)~GPIO_PUPDR_PUPD5;
    */

    GPIOB->MODER &= (uint32_t)~GPIO_MODER_MODE5;
    GPIOB->MODER |= (uint32_t)GPIO_MODER_MODE5_1;   
    GPIOB->AFR[0] &= (uint32_t)~GPIO_AFRL_AFRL5;
    GPIOB->AFR[0] |= (uint32_t)~GPIO_AFRL_AFSEL5_1;

    RCC->APB1RSTR1 |= (uint32_t)RCC_APB1ENR1_TIM3EN;
    TIM3->ARR = (uint32_t)16000000u;
    TIM3->CCMR1 |= (uint32_t)TIM_CCMR1_CC1S_1;
    TIM3->CCER |= (uint32_t)TIM_CCER_CC1E;
    TIM3->DIER |= TIM_DIER_CC1DE;
    TIM3->CR1 |= TIM_CR1_CEN;

    RCC->CFGR &= (uint32_t)~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV2;

    RCC->CFGR &= (uint32_t)~RCC_CFGR_PPRE1_Msk;
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV4;

    TIM2->PSC &= (uint32_t)~TIM_PSC_PSC_Msk;

    RCC->APB1ENR1 |= (uint32_t)RCC_APB1ENR1_TIM2EN;
    /* TIM2->EGR */
    TIM2->ARR = (uint32_t)16000000u;
    TIM2->PSC = 0u;
    TIM2->EGR |= (uint32_t)TIM_EGR_UG;
    TIM2->DIER |= (uint32_t)TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 0u);

    TIM2->CR1 |= (uint32_t)TIM_CR1_CEN;

    while(1)
    {

        timerCntr = TIM2->CNT;




        /*
        if (GPIO_IDR_ID5 == (GPIO_IDR_ID5_Msk & GPIOB->IDR))
        {
            GPIOB->BSRR = GPIO_BSRR_BS8;
        }
        else
        {
            GPIOB->BRR = GPIO_BSRR_BR8;
        }
        */
        /*
        volatile uint32_t i;

        GPIOB->BSRR = GPIO_BSRR_BS8;

        for(i = 0u; i < 1000000u; i++)
        {
        }

        GPIOB->BRR = GPIO_BSRR_BS8;

        for(i = 0u; i < 1000000u; i++)
        {
        }
        */
    }
}