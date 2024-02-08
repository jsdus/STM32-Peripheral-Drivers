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


//Peripheral Clock Setup

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/* Init and De-init */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

// Data send and receive
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);


//IRQ Configuration and ISR Handling

void SPI_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

//Orhter Peripheral Controls
#endif /* INC_STM32F103RB_SPI_DRIVER_H_ */