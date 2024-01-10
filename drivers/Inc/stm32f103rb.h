/*
 * stm32103rb.h
 *
 *  Created on: Jan 8, 2024
 *      Author: djack
 */

#ifndef INC_STM32F103RB_H_
#define INC_STM32F103RB_H_

#include <stdint.h>

#define __vo	volatile

/* Base  addresses of Flash and SRAM memories */


#define FLASH_BASEADDR					0x08000000U		/* Base address of flash memory */
#define SRAM1_BASEADDR					0x20000000U		/* Base address of SRAM1,this specific board only has one SRAM */
#define ROM_BASEADDR					0x1FFFF000U		/* Base address of ROM/ System memory */
#define SRAM 							SRAM1_BASEADDR	/* Base address of SRAM, just SRAM1 */

/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASE						0x40000000U
#define APB1PERIPH_BASE					PERIPH_BASE
#define APB2PERIPH_BASE					0x40010000U
#define AHBPERIPH_BASE					0x40018000U

/*
 * Base addresses of peripherals which are hanging on APB2 bus
 */

#define GPIOA_BASEADDR					(APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASEADDR					(APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASEADDR					(APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASEADDR					(APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASEADDR					(APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASEADDR					(APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASEADDR					(APB2PERIPH_BASE + 0x2000)
#define SPI1_BASEADDR					(APB2PERIPH_BASE + 0x3000)
#define EXTI_BASEADDR					(APB2PERIPH_BASE + 0x0400)
#define USART1_BASEADDR					(APB2PERIPH_BASE + 0x3800)
#define AFIO_BASEADDR					(APB2PERIPH_BASE + 0x0000)

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 */

#define SPI2_BASEADDR					(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR					(APB1PERIPH_BASE + 0x3C00)
#define USART2_BASEADDR					(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR					(APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR					(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR					(APB1PERIPH_BASE + 0x5000)
#define I2C1_BASEADDR					(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR					(APB1PERIPH_BASE + 0x5800)

/*
 * Base addresses of peripherals which are hanging on AHB bus
 */

#define RCC_BASEADDR					(AHBPERIPH_BASE + 0x1000)


typedef struct
{
	__vo uint32_t CRL;
	__vo uint32_t CRH;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t BRR;
	__vo uint32_t LCKR;
}GPIO_RegDef_t;

#define GPIOA		((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB		((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC		((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE		((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF		((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG		((GPIO_RegDef_t*)GPIOG_BASEADDR)

typedef struct
{
	__vo uint32_t EVCR;
	__vo uint32_t MAPR;
	__vo uint32_t EXTICR1;
	__vo uint32_t EXTICR2;
	__vo uint32_t EXTICR3;
	__vo uint32_t EXTICR4;
	__vo uint32_t MAPR2;
}AFIO_RegDef_t;

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t AHBSTR;
	__vo uint32_t CFGR2;
}RCC_RegDef_t;

#define RCC 		((RCC_RegDef_t*)RCC_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()		(RCC->APB2ENR |= (1<<2))
#define GPIOB_PCLK_EN()		(RCC->APB2ENR |= (1<<3))
#define GPIOC_PCLK_EN()		(RCC->APB2ENR |= (1<<4))
#define GPIOD_PCLK_EN()		(RCC->APB2ENR |= (1<<5))
#define GPIOE_PCLK_EN()		(RCC->APB2ENR |= (1<<6))

/*
 * Clock Enable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))

/*
 * Clock Enable Macros for SPIx peripherals
 */

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))

/*
 * Clock Enable Macros for USARTx peripherals
 */

#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()		(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()		(RCC->APB1ENR |= (1 << 20))

/*
 * Clock Disable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()		(RCC->APB2ENR &= (1<<2))
#define GPIOB_PCLK_DI()		(RCC->APB2ENR &= (1<<3))
#define GPIOC_PCLK_DI()		(RCC->APB2ENR &= (1<<4))
#define GPIOD_PCLK_DI()		(RCC->APB2ENR &= (1<<5))
#define GPIOE_PCLK_DI()		(RCC->APB2ENR &= (1<<6))

/*
 * Clock Disable Macros for I2Cx peripherals
 */

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= (1 << 21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= (1 << 22))

/*
 * Clock Disable Macros for SPIx peripherals
 */

#define SPI1_PCLK_DI()		(RCC->APB2ENR &= (1 << 12))
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= (1 << 14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= (1 << 15))

/*
 * Clock Disable Macros for USARTx peripherals
 */

#define USART1_PCLK_DI()	(RCC->APB2ENR &= (1 << 14))
#define USART2_PCLK_DI()	(RCC->APB1ENR &= (1 << 17))
#define USART3_PCLK_DI()	(RCC->APB1ENR &= (1 << 18))
#define UART4_PCLK_DI()		(RCC->APB1ENR &= (1 << 19))
#define UART5_PCLK_DI()		(RCC->APB1ENR &= (1 << 20))

//generic macros
#define ENABLE 			1
#define DISABLE 		0
#define SET  			ENABLE
#define RESET  			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#endif /* INC_STM32F103RB_H_ */
