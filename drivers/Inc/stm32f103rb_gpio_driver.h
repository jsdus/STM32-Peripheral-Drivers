/*
 * stm32f103rb_gpio_driver.h
 *
 *  Created on: Jan 9, 2024
 *      Author: djack
 */

#ifndef INC_STM32F103RB_GPIO_DRIVER_H_
#define INC_STM32F103RB_GPIO_DRIVER_H_

#include "stm32f103rb.h"

/*
 * This is a configuration structure for a GPIO pin
 */
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinInMode;
	uint8_t GPIO_PinOutMode;
	uint8_t GPIO_PinPuPdControl;


}GPIO_PinConfig_t;

/*
 * This is the handle structure for a GPIO pin
 */

typedef struct
{
	// point to hold the base address of the GPIO  peripheral
	GPIO_RegDef_t *pGPIOx; /* holds base address of GPIO port*/
	GPIO_PinConfig_t GPIO_PinConfig; /* holds GPIO pin configuration settings */

}GPIO_Handle_t;

/*
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

/*
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT10		1
#define GPIO_MODE_OUT2		2
#define GPIO_MODE_OUT50		3

/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OP		1
#define GPIO_OP_TYPE_APP	2
#define GPIO_OP_TYPE_AOP	3

/*
 * GPIO pin possible input types
 */
#define GPIO_IP_TYPE_AM		0
#define GPIO_IP_TYPE_FI		1
#define GPIO_IP_TYPE_PUPD	2

/*
 * GPIO pin pull-up pull-down controls
 */
#define PULLUP				1
#define PULLDOWN			0



/*
 * APIs Supported by driver
 */

/* Init and De-init */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/* Peripheral Clock Setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/* Data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,  uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/* IRQ handling */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32F103RB_GPIO_DRIVER_H_ */
 
