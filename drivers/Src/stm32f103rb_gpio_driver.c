#include "stm32f103rb_gpio_driver.h"

/* Init and De-init */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;  //temporary register
	pGPIOHandle->pGPIOx->CRL = 0;
	pGPIOHandle->pGPIOx->CRH = 0;

	// 1. Configure the mode
	if ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)<= 7)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(4 *pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->CRL |= temp;
		temp = 0;
	}else
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber-8)));
		pGPIOHandle->pGPIOx->CRH |= temp;
		temp = 0;
	}


	// 2. Configure the configuration
	if (((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)<= 7) && (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == 00 ))
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinInMode<<(2+(4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
		pGPIOHandle->pGPIOx->CRL |= temp;
		temp = 0;
	}else if (((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)>7) && (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == 00 ))
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinInMode<<(2+(4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber-8))));
		pGPIOHandle->pGPIOx->CRH |= temp;
		temp = 0;
	}
	if (((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)<= 7) && (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode > 00 ))
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOutMode<<(2+(4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
		pGPIOHandle->pGPIOx->CRL |= temp;
		temp = 0;
	}else if (((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)>7) && (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode > 00 ))
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOutMode<<(2+(4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber-8))));
		pGPIOHandle->pGPIOx->CRH |= temp;
		temp = 0;
	}

	// 3. Configure the pupd settings
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_IP_TYPE_PUPD)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->ODR |= temp;
		temp = 0;
	}
}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}
}

/* Peripheral Clock Setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}else if (pGPIOx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}else if (pGPIOx == GPIOC)
				{
					GPIOC_PCLK_DI();
				}else if (pGPIOx == GPIOD)
				{
					GPIOD_PCLK_DI();
				}else if (pGPIOx == GPIOE)
				{
					GPIOE_PCLK_DI();
				}
	}
}

/* Data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001 );
	return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,  uint16_t Value)
{
	pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}

/* IRQ handling */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
