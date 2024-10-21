/*
 * GPIO.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Dnyaneshwar Galdhar
 */


 #include "GPIO.h"

status_t GPIO_ClockConfig(GPIO_RegDef_t* pGPIOx, uint8_t EnorDi)
{
	if(pGPIOx == NULL)
		return(PTR_INVALID_VAL_ERROR);
	if(ENABLE == EnorDi)
	{
		if(GPIOA == pGPIOx)
			GPIOA_PCLK_EN();
		else if(GPIOB == pGPIOx)
			GPIOB_PCLK_EN();
		else if(GPIOC == pGPIOx)
			GPIOC_PCLK_EN();
		else if(GPIOD == pGPIOx)
			GPIOD_PCLK_EN();
		else if(GPIOE == pGPIOx)
			GPIOE_PCLK_EN();
		else if(GPIOF == pGPIOx)
			GPIOF_PCLK_EN();
		else if(GPIOG == pGPIOx)
			GPIOG_PCLK_EN();
		else
			return(FAIL);
	}
	else if(DISABLE == EnorDi)
	{
		if(GPIOA == pGPIOx)
			GPIOA_PCLK_DI();
		else if(GPIOB == pGPIOx)
			GPIOB_PCLK_DI();
		else if(GPIOC == pGPIOx)
			GPIOC_PCLK_DI();
		else if(GPIOD == pGPIOx)
			GPIOD_PCLK_DI();
		else if(GPIOE == pGPIOx)
			GPIOE_PCLK_DI();
		else if(GPIOF == pGPIOx)
			GPIOF_PCLK_DI();
		else if(GPIOG == pGPIOx)
			GPIOG_PCLK_DI();
		else
			return(FAIL);
	}
	else
	{
		return(INPUT_VALUE_ERROR);
	}


	return(SUCCESS);
}

status_t GPIO_Init(GPIO_Handle_t* GPIO_Handle)
{
	uint8_t temp1, temp2;
	if(NULL == GPIO_Handle->pGPIOx)
		return (PTR_INVALID_VAL_ERROR);

	// 1. Enable the Peripheral Clock
	GPIO_ClockConfig(GPIO_Handle->pGPIOx, ENABLE);

	temp1 = GPIO_Handle->GPIO_PinConfig.GPIO_PinNumber / 8;	// Useful to choose Reg low or High according to pin
	temp2 = GPIO_Handle->GPIO_PinConfig.GPIO_PinNumber % 8; // Useful to select bit position according to pin

	//2. Mode and config settings
	if(GPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IN)
	{
		//3. INPUT Mode
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] &= ~(GPIO_Handle->GPIO_PinConfig.GPIO_PinMode << (4*temp2) );
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] |= (GPIO_Handle->GPIO_PinConfig.GPIO_PinMode << (4*temp2) );

		//4. Config settings for INPUT mode
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] &= ~(GPIO_Handle->GPIO_PinConfig.GPIO_PinAnalogIN_PuPdControl << ((4*temp2)+2));
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] |= (GPIO_Handle->GPIO_PinConfig.GPIO_PinAnalogIN_PuPdControl << ((4*temp2)+2));

	}
	else if(GPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_OUT)
	{
		//5. Output speed
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] &= ~(GPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed << (4*temp2) );
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] |= (GPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed << (4*temp2) );

		//6. Output config
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] &= ~(GPIO_Handle->GPIO_PinConfig.GPIO_Pin_GP_AF_OPType << ((4*temp2)+2));
		GPIO_Handle->pGPIOx->GPIOx_CTR[temp1] |= (GPIO_Handle->GPIO_PinConfig.GPIO_Pin_GP_AF_OPType << ((4*temp2)+2));

	}
	else
	{
		return(INPUT_VALUE_ERROR);
	}


	// 7. Config Alt Func
		// To-Do
	// 8. Interrupt
		// To-Do
	return (SUCCESS);

}

status_t GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
{
	// 1. Disable Peripheral Clock: The peripheral's clock is disabled to save power, as the peripheral is no longer needed.
	GPIO_ClockConfig(pGPIOx, DISABLE);
	// 2.Reset Peripheral Registers: The configuration registers (such as control, status, and data registers) are reset to their default states. This prevents any unintended side effects from the previous configuration.
		// To-Do
	// 3. Disable Interrupts: If the peripheral had interrupts enabled, they should be disabled to avoid unexpected interrupts after de-initialization.
		// To-Do
	// 4. Release GPIO Pins: If the peripheral was using any GPIO pins, they should be released (reset to their default state, typically input mode) so they can be used by other peripherals or functions.
		// To-Do
	// 5. Turn Off Peripheral Specific Features: Any peripheral-specific features like DMA, timers, or communication modes (e.g., I2C, SPI) should be disabled or reset.
		// To-Do
	// 6. Clear Peripheral Buffers/Flags: Clear any data buffers, flags, or pending interrupts associated with the peripheral.
		// To-Do
	// 7. Power Down the Peripheral: If the peripheral supports power management, power down or place the peripheral in a low-power state.
		// To-Do
	return(SUCCESS);
}


status_t GPIO_WritePin(GPIO_RegDef_t* pGPIOx,uint8_t GPIO_PinNumber, uint8_t value)
{
	if(pGPIOx == NULL)
		return(PTR_INVALID_VAL_ERROR);

	if(value == SET)
	{
		pGPIOx->GPIOx_BSRR |= (1 << GPIO_PinNumber);
	}
	else
	{
		pGPIOx->GPIOx_BSRR |= (1 << (GPIO_PinNumber + 16));
	}

	return(SUCCESS);
}

status_t GPIO_WritePort(GPIO_RegDef_t* pGPIOx, uint16_t value)
{
	if(pGPIOx == NULL)
		return(PTR_INVALID_VAL_ERROR);

	pGPIOx->GPIOx_ODR = value;

	return(SUCCESS);
}

status_t GPIO_TogglePin(GPIO_RegDef_t* pGPIOx, uint8_t GPIO_PinNumber)
{
	if(pGPIOx == NULL)
		return(PTR_INVALID_VAL_ERROR);

	pGPIOx->GPIOx_ODR ^= (1 << GPIO_PinNumber);

	return(SUCCESS);
}

