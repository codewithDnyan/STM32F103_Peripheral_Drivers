/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
 

#include <stdint.h>
#include "stm32f103xx.h"
#include "GPIO.h"

#define LED_SET		(CLEAR)
#define LED_CLEAR	(SET)
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay(void)
{
	for(int i = 0; i < 1000; ++i)
		for(int j = 0; j < 500; ++j)
			;
}

int main(void)
{
    /* Loop forever */
	GPIO_PinConfig_t UserLED;
	GPIO_Handle_t LED_Handle;
	UserLED.GPIO_PinNumber = GPIO_PIN_NO_13;
	UserLED.GPIO_PinMode = GPIO_MODE_OUT;
	UserLED.GPIO_PinSpeed = GPIO_MODE_OUT_SPEED_2MHZ;
	UserLED.GPIO_Pin_GP_AF_OPType = GPIO_PP_OUTPUT;

	LED_Handle.pGPIOx = GPIOC;
	LED_Handle.GPIO_PinConfig = UserLED;

	GPIO_Init(&LED_Handle);
	for(;;)
	{
		GPIO_TogglePin(GPIOC, GPIO_PIN_NO_13);
		delay();
		GPIO_TogglePin(GPIOC, GPIO_PIN_NO_13);
		delay();
		GPIO_WritePin(GPIOC, GPIO_PIN_NO_13, LED_SET);
		delay();
		GPIO_WritePin(GPIOC, GPIO_PIN_NO_13, LED_CLEAR);
		delay();
	}

	return(SUCCESS);
}