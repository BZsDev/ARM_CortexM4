#include <stdint.h>
#include "GPIO.h"


/**
 * @brief This function is a blank function.
 * @param void
 * @return void
 */
void Test_Blank(void);

/**
 * @brief This function is testing the GPIO output setup by set/reset the builtin led with simple for loops.
 * @param void
 * @return void
 */
void Test_GPIO_Out_Toggle_1(void);

/**
 * @brief This function is testing the GPIO output setup by toggleing the builtin led with simple for loops.
 * @param void
 * @return void
 */
void Test_GPIO_Out_Toggle_2(void);

/**
 * @brief Toogle builtin led with timer but without interrupt.
 * @param void
 * @return void
 */
void Test_Timer_1(void);

void TIM3_IRQHandler(void);

/**
 * @brief Toogle builtin led with timer and interrupt.
 * @param void
 * @return void
 */
void Test_Timer_2(void);

/**
 * @brief Simple program for driving the builtin led with PWM.
 * @param void
 * @return void
 */
void Test_PWM_1(void);

/**
 * @brief Example function. Simple LED toggling with GPIO input.
 * @param void
 * @return void
 */
void Test_GPIO_DigitalRead_1(void);

/**
 * @brief Example function. Simple ADC single conversion.
 * @param void
 * @return void
 */
void Test_ADC_Single_1(void);

/**
 * @brief Example function. Simple UART transmission.
 * @param void
 * @return void
 */
void Test_UART_TransmitterSingle_1(void);

/**
 * @brief Example function. Simple UART receiver function with busy-waiting.
 * @param void
 * @return void
 */
void Test_UART_ReceiverSingle_1(void);

void USART2_IRQHandler(void);

/**
 * @brief Example function. Simple UART receiver and transmitter function with interrupt.
 * @param void
 * @return void
 */
void Test_UART_ReceiverTransmitterSingleInterrupt_1(void);

void UARTInit_1(void);

/**
 * @brief Example function. Float32 UART transmission.
 * @param void
 * @return void
 */
void Test_UART_TransmitterFloat_1(void);