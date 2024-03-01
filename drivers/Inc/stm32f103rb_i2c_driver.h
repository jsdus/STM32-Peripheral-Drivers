#ifndef INC_STM32F103RB_I2C_DRIVER_H_
#define INC_STM32F103RB_I2C_DRIVER_H_

#include "stm32f103rb.h"


//I2C Configuration
typedef struct 
{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_ACKControl;
    uint16_t I2C_FMDutyCycle;

}I2C_Config_t;

typedef struct 
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2C_Config;

}I2C_Handle_t;

//SCL Speed
#define I2C_SCL_SPEED_SM    100000
#define I2C_SCL_SPEED_FM4K  400000
#define I2C_SCL_SPEED_FM2k  200000

//ACK control
#define I2C_ACK_ENABLE      1
#define I2C_ACK_DISABLE     0


//Duty Cycle
#define I2C_FM_DUTY_2       0
#define I2C_FM_DUTY_16_9    1


//I2C Status Flags
#define I2C_SB_FLAG         (1 << 0)
#define I2C_TXE_FLAG        (1 << 7)
#define I2C_RXNE_FLAG       (1 << 6)
#define I2C_OVR_FLAG        (1 << 11)
#define I2C_AF_FLAG         (1 << 10)
#define I2C_ARLO_FLAG       (1 << 9)
#define I2C_BERR_FLAG       (1 << 8)
#define I2C_STOPF_FLAG      (1 << 4)
#define I2C_ADD10_FLAG      (1 << 3)
#define I2C_BTF_FLAG        (1 << 2)
#define I2C_ADDR_FLAG       (1 << 1)
#define I2C_TIMEOUT_FLAG    (1 << 14)


//Peripheral Clock Setup

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/* Init and De-init */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

// Data send and receive
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr);

//IRQ Configuration and ISR Handling

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

//Orhter Peripheral Controls

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

#endif /* INC_STM32F103RB_I2C_DRIVER_H_ */
