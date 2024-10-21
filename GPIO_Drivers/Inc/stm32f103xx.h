/*
 * stm32f103xx.h
 *
 *  Created on: Aug 31, 2024
 *  Author: Dnyaneshwar Galdhar
 */


#ifndef STM32F103XX_H_
#define STM32F103XX_H_

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>


// 0. Common symbolic constants
#define SUCCESS				0
#define FAIL				1
#define FALSE				0
#define TRUE				1
#define ENABLE				1
#define DISABLE 			0
#define SET					1
#define CLEAR				0
#define GPIO_PIN_SET		(SET)
#define GPIO_PIN_CLEAR		(CLEAR)

// Symbolic constants for Errors
#define INPUT_VALUE_ERROR			2
#define PTR_INVALID_VAL_ERROR		3

//USER IO

typedef uint8_t 	status_t;
typedef volatile	__vo;

//1. Define Base Addr of Peripheral Buses
#define PERIPHERAL_BASE		(0x40000000u)
#define APB1_BASE_ADDR		(PERIPHERAL_BASE)
#define APB2_BASE_ADDR		(0x40010000u)
#define AHB_BASE_ADDR		(0x40018000u)

// 2. Define Base Addr of Peripherals on Each Peripheral Bus
// 2.1 Peripherals on APB2 Peripheral Bus
#define AFIO_BASE_ADDR     	(APB2_BASE_ADDR)
#define GPIOA_BASE_ADDR		(APB2_BASE_ADDR + 0x0800)
#define GPIOB_BASE_ADDR		(APB2_BASE_ADDR + 0x0C00)
#define GPIOC_BASE_ADDR		(APB2_BASE_ADDR + 0x1000)
#define GPIOD_BASE_ADDR		(APB2_BASE_ADDR + 0x1400)
#define GPIOE_BASE_ADDR		(APB2_BASE_ADDR + 0x1800)
#define GPIOF_BASE_ADDR		(APB2_BASE_ADDR + 0x1C00)
#define GPIOG_BASE_ADDR		(APB2_BASE_ADDR + 0x2000)


//2.2 Peripherals on APB1 Peripheral Bus
//---------------- TO-DO -----------------

//2.3 Peripherals on AHB Peripheral Bus
#define RCC_BASE_ADDR		(0X40021000u)
//---------------- TO-DO -----------------


//3. Peripheral Register Struct Definition
typedef struct
{
	uint32_t AFIO_EVCR;			/* Addr offset: 0x00 */
	uint32_t AFIO_MAPR;			/* Addr offset: 0x04 */
	uint32_t AFIO_EXTICR1;		/* Addr offset: 0x08 */
	uint32_t AFIO_EXTICR2;		/* Addr offset: 0x0C */
	uint32_t AFIO_EXTICR3;		/* Addr offset: 0x10 */
	uint32_t AFIO_EXTICR4;		/* Addr offset: 0x14 */
	uint32_t Res;				/* Addr offset: 0x18 */
	uint32_t AFIO_MAPR2;		/* Addr offset: 0x1C */
}AFIO_RegDef_t;

typedef struct
{
	uint32_t GPIOx_CTR[2]; 		/* Addr offset: 0x00 */
	uint32_t GPIOx_IDR; 		/* Addr offset: 0x08 */
	uint32_t GPIOx_ODR; 		/* Addr offset: 0x0C */
	uint32_t GPIOx_BSRR; 		/* Addr offset: 0x10 */
	uint32_t GPIOx_BRR; 		/* Addr offset: 0x14 */
	uint32_t GPIOx_LCKR; 		/* Addr offset: 0x18 */
}GPIO_RegDef_t;

typedef struct
{
	uint32_t RCC_CR;			/* Addr offset: 0x00 */
	uint32_t RCC_CFGR; 			/* Addr offset: 0x04 */
	uint32_t RCC_CIR; 			/* Addr offset: 0x08 */
	uint32_t RCC_APB2RSTR; 		/* Addr offset: 0x0C */
	uint32_t RCC_APB1RSTR; 		/* Addr offset: 0x10 */
	uint32_t RCC_AHBENR; 		/* Addr offset: 0x14 */
	uint32_t RCC_APB2ENR; 		/* Addr offset: 0x18 */
	uint32_t RCC_APB1ENR; 		/* Addr offset: 0x1C */
	uint32_t RCC_BDCR;			/* Addr offset: 0x20 */
	uint32_t RCC_CSR;			/* Addr offset: 0x24 */
}RCC_RegDef_t;

// 4. Create GPIO symbolic constant with value as GPIOx base addr type casted to GPIO_RegDef struct
#define GPIOA				((GPIO_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB				((GPIO_RegDef_t*)GPIOB_BASE_ADDR)
#define GPIOC				((GPIO_RegDef_t*)GPIOC_BASE_ADDR)
#define GPIOD				((GPIO_RegDef_t*)GPIOD_BASE_ADDR)
#define GPIOE				((GPIO_RegDef_t*)GPIOE_BASE_ADDR)
#define GPIOF				((GPIO_RegDef_t*)GPIOF_BASE_ADDR)
#define GPIOG				((GPIO_RegDef_t*)GPIOG_BASE_ADDR)
#define RCC					((RCC_RegDef_t*)RCC_BASE_ADDR)

//5. Clock EN macros for Peripheral
//5.1 Clock EN for AFIO
#define AFIO_PCLK_EN()    		( RCC->RCC_APB2ENR |= (1 << 0) )
//5.2 Clock EN for GPIO
#define GPIOA_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 2) )
#define GPIOB_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 3) )
#define GPIOC_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 4) )
#define GPIOD_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 5) )
#define GPIOE_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 6) )
#define GPIOF_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 7) )
#define GPIOG_PCLK_EN()			( RCC->RCC_APB2ENR |= (1 << 8) )


//6. Clock DI macros for Peripheral
//6.1 Clock DI for AFIO
#define AFIO_PCLK_DI()    		( RCC->RCC_APB2ENR &= ~(1 << 0) )
//6.2 Clock DI for GPIO
#define GPIOA_PCLK_DI() 		( RCC-> RCC_APB2ENR &= ~(1 << 2) )
#define GPIOB_PCLK_DI() 		( RCC-> RCC_APB2ENR &= ~(1 << 3) )
#define GPIOC_PCLK_DI() 		( RCC-> RCC_APB2ENR &= ~(1 << 4) )
#define GPIOD_PCLK_DI()			( RCC-> RCC_APB2ENR &= ~(1 << 5) )
#define GPIOE_PCLK_DI() 		( RCC-> RCC_APB2ENR &= ~(1 << 6) )
#define GPIOF_PCLK_DI() 		( RCC-> RCC_APB2ENR &= ~(1 << 7) )
#define GPIOG_PCLK_DI() 		( RCC-> RCC_APB2ENR &= ~(1 << 8) )


/
#endif /* STM32F103XX_H_ */
