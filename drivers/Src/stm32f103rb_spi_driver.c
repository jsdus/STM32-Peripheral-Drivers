#include "stm32f103rb_spi_driver.h"

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if (pGPIOx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if (pGPIOx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1
				{
					SPI1_PCLK_DI();
				}else if (pSPIx == SPI2)
				{
					SPI2_PCLK_DI();
				}else if (pSPIx == SPI3)
				{
					SPI3_PCLK_DI();
				}
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t tempreg = 0;
	//device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << 2;
	//Bus config
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD )
	{
		tempreg &= ~(1 <<15);
	}else if (pSPIHandle -> SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tempreg |= ~(1 <<15);
	}else if (pSPIHandle -> SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		tempreg &= ~(1 <<15);
		tempreg |= ~(1 <<10);
	}

	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << 3;

	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << 11;
	
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << 1;

	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << 0;

	pSPIHandle->pSPIx->CR1 = tempreg;
}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_SendData (SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//wait until TxE = 0
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);

		//check DFF
		if((pSPIx->CR1 & (1 << 11)))
		{
			//16 bit
			//load data ( must cast to 16 bit or else will only load 1 byte)
			pSPIx->DR = *((uint16_t*) pTxBuffer );
			Len--;
			Len--;
			(uint16_t*) pTxBuffer++;
		}else
		{
			//8 bit
			pSPIx-> DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}


	}	
}