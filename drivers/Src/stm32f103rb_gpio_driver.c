#include "stm32f103rb_gpio_driver.h"

/* Init and De-init */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;  //temporary register
	// 1. Configure the mode
	if ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)<= 7)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(4*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->CRL = temp;
		temp = 0;
	}else
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(4*(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber-8)));
		pGPIOHandle->pGPIOx->CRH = temp;
		temp = 0;
	}


	// 2. Configure the speed
	// 3. Configure the pupd settings

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

}

/* Peripheral Clock Setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIO == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIO == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIO == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIO == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}else if (pGPIO == GPIOB)
				{
					GPIOB_PCLK_DI();
				}else if (pGPIO == GPIOC)
				{
					GPIOC_PCLK_DI();
				}else if (pGPIO == GPIOD)
				{
					GPIOD_PCLK_DI();
				}else if (pGPIO == GPIOE)
				{
					GPIOE_PCLK_DI();
				}
	}
}

/* Data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{

}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,  uint16_t Value)
{

}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{

}

/* IRQ handling */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
