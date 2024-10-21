/*
 * GPIO.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Dnyaneshwar Galdhar
 */


#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f103xx.h"

// GPIO Port Mode
#define GPIO_MODE_IN 					0
#define GPIO_MODE_OUT					1

// GPIO OUTPUT Speed
#define GPIO_MODE_OUT_SPEED_10MHZ		1
#define GPIO_MODE_OUT_SPEED_2MHZ		2
#define GPIO_MODE_OUT_SPEED_50MHZ		3

// GPIO Output Config
#define GPIO_PP_OUTPUT					0 //(0b00)
#define GPIO_OD_OUTPUT					1 //(0b01)
#define GPIO_ALT_FUN_PP_OUTPUT			2 //(0b10)
#define GPIO_ALT_FUN_OD_OUTPUT			3 //(0b11)

// GPIO Input Config
#define GPIO_ANALOG_INPUT_EN   		 	0 //(0b00)
#define GPIO_FLOATING_INPUT				1 //(0b01)
#define GPIO_PUPD_INPUT					2 //(0b10)

// GPIO_PIN_NUMBER
#define GPIO_PIN_NO_0				0
#define GPIO_PIN_NO_1				1
#define GPIO_PIN_NO_2 				2
#define GPIO_PIN_NO_3 				3
#define GPIO_PIN_NO_4 				4
#define GPIO_PIN_NO_5 				5
#define GPIO_PIN_NO_6 				6
#define GPIO_PIN_NO_7 				7
#define GPIO_PIN_NO_8 				8
#define GPIO_PIN_NO_9 				9
#define GPIO_PIN_NO_10 				10
#define GPIO_PIN_NO_11 				11
#define GPIO_PIN_NO_12 				12
#define GPIO_PIN_NO_13 				13
#define GPIO_PIN_NO_14 				14
#define GPIO_PIN_NO_15 				15


typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;					// GPIO PIN MODE Select
	uint8_t GPIO_PinSpeed;					// Output Speed Config
	uint8_t GPIO_Pin_GP_AF_OPType;			// OUTPUT Config
	uint8_t GPIO_PinAnalogIN_PuPdControl;	// INPUT  Config
	uint8_t GPIO_PinAltFunction;			// Alternate Config
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t* pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

// Basic GPIO Config
status_t GPIO_Init(GPIO_Handle_t* GPIO_Handle);
status_t GPIO_DeInit(GPIO_RegDef_t* pGPIOx);
status_t GPIO_ClockConfig(GPIO_RegDef_t* pGPIOx, uint8_t EnorDi);

// GPIO Data Read/Write
uint8_t GPIO_ReadPin(GPIO_RegDef_t* pGPIOx, uint8_t GPIO_PinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx);
status_t GPIO_WritePin(GPIO_RegDef_t* pGPIOx,uint8_t GPIO_PinNumber, uint8_t value);
status_t GPIO_WritePort(GPIO_RegDef_t* pGPIOx, uint16_t value);
status_t GPIO_TogglePin(GPIO_RegDef_t* pGPIOx, uint8_t GPIO_PinNumber);

// Interrupt Config and Handling APIs
status_t GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
status_t GPIO_IRQHandle(uint8_t PinNumber);

// Alternate Function APIs



#endif /* GPIO_H_ */
