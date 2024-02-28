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

//Device Mode
#define SPI_DEVICE_MODE_MASTER			1
#define SPI_DEVICE_MODE_SLAVE			0

//Bus Config
#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3

//SCLK SPeed
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

//DFF
#define SPI_DFF_8BITS					0
#define SPI_DFF_16BITS					1

//CPOL
#define SPI_CPOL_HIGH					1
#define SPI_CPOL_LOW					0
 
 //CPHA
 #define SPI_CPHA_HIGH					1
 #define SPI_CPHA_LOW					0

 //SSM
 #define SPI_SSM_EN						1
 #define SPI_SSM_DI						0


#define SPI_TXE_FLAG	(1<< 1)
#define SPI_RXNE_FLAG 	(1 << 0)
#define SPI_BUSY_FLAG	(1 << 7)

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

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
#endif /* INC_STM32F103RB_SPI_DRIVER_H_ */