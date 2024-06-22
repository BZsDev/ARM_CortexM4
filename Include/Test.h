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
void Test_GPIO_Toggle_1(void);

/**
 * @brief This function is testing the GPIO output setup by toggleing the builtin led with simple for loops.
 * @param void
 * @return void
 */
void Test_GPIO_Toggle_2(void);

/**
 * @brief Toogle builtin led with timer but without interrupt.
 * @param void
 * @return void
 */
void Test_Timer_1(void);

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
