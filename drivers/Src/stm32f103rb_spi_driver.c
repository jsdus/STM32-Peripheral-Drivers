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
