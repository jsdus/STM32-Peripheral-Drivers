#ifndef INC_STM32F103RB_SPI_DRIVER_H_
#define INC_STM32F103RB_SPI_DRIVER_H_

#include "stm32f103rb.h"

//SPI configuration structure
typedef struct 
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_config_t;


//SPI Handle structure

typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_config_t SPIConfig;

}SPI_Handle_t;

#endif /* INC_STM32F103RB_SPI_DRIVER_H_ */