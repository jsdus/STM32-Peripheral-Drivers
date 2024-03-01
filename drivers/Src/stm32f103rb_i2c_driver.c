#include "stm32f103rb_i2c_driver.h"

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= ( 1 << 8);
}

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr <<1;
    SlaveAddr &= ~(1); //Slave addr + r/w bit
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
    uint32_t dummyRead = pI2Cx->SR1;
    dummyRead = pI2Cx->SR2;
    (void)dummyRead;

}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx -> CR1 |= (1<<9);
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pI2Cx -> CR1 |= (1 << 0);

    }else
    {
        pI2Cx -> CR1 &= ~(1<<0);
    }
}

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_EN();
        }else if (pI2Cx == I2C2)
        {
        I2C2_PCLK_EN();
        }
    }else
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_DI();
        }else if (pI2Cx == I2C2)
        {
        I2C2_PCLK_DI();
        }
    }
}

uint32_t RCC_GetPLLOutputClock()
{
    return 0;
}

uint16_t AHB_PreScaler[8] = {2,4,8,16,128,256, 512};
uint16_t APB1_PreScaler[8] = {2,4,8, 16};

uint32_t RCC_GetPCLK1Value(void)
{
    uint32_t pclk1, SystemClk;
    uint8_t clksrc, temp, ahbp, apb1p;

    clksrc = ((RCC -> CFGR >> 2)) & 0x3;

    if(clksrc == 0)
    {
        SystemClk = 8000000;

    }else if (clksrc == 1)
    {
        SystemClk = 16000000;

    }else if (clksrc == 2)
    {
        SystemClk = RCC_GetPLLOutputClock();
    }

    temp = (RCC -> CFGR >> 4) & 0xF;

    if (temp<8)
    {
        ahbp = 1;

    }else
    {
        ahbp = AHB_PreScaler[temp-8];
    }

    temp = (RCC -> CFGR >> 10) & 0x7;

    if (temp<4)
    {
        apb1p = 1;

    }else
    {
        ahbp = APB1_PreScaler[temp-4];
    }

    pclk1 = (SystemClk/ahbp) / apb1p;

    return pclk1;
}
/* Init and De-init */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;
    //ACK control
    tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << 10; 
    pI2CHandle->pI2Cx->CR1 = tempreg;

    //FREQ
    tempreg = 0;
    tempreg |= RCC_GetPCLK1Value()/1000000U;
    pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

    //device own address
    tempreg |= pI2CHandle -> I2C_Config.I2C_DeviceAddress << 1;
    tempreg |= (1<<14);
    pI2CHandle -> pI2Cx -> OAR1 = tempreg;
    
    //CCR calc
    uint16_t ccr_value = 0;
    tempreg = 0;

    if(pI2CHandle -> I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        //standard mode
        ccr_value = RCC_GetPCLK1Value()/(2*pI2CHandle -> I2C_Config.I2C_SCLSpeed);
        tempreg |= (ccr_value & 0xFFF);
    }else
    {
        //fast mode
        tempreg |= (1<<15);
        tempreg |= (pI2CHandle -> I2C_Config.I2C_FMDutyCycle << 14);
        
        if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value = RCC_GetPCLK1Value()/(3*pI2CHandle -> I2C_Config.I2C_SCLSpeed);
        }else
        {
            ccr_value = RCC_GetPCLK1Value()/(25*pI2CHandle -> I2C_Config.I2C_SCLSpeed);
        }

        tempreg |= (ccr_value & 0xFFF);
    }
    pI2CHandle -> pI2Cx->CCR = tempreg;

    //TRISE
    if (pI2CHandle -> I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {

        tempreg = (RCC_GetPCLK1Value() / 1000000U) + 1;

    }else
    {
        tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;

    }
    pI2CHandle -> pI2Cx->TRISE = (tempreg & 0x3F);

}
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{

}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr)
{
    //Start condition
    I2C_GenerateStartCondition(pI2CHandle -> pI2Cx);

    //wait until SB set
    while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SB_FLAG));
    
    //Send Addr of slave
    I2C_ExecuteAddressPhase(pI2CHandle ->pI2Cx,SlaveAddr);

    //confirm completion of address phase
    while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_ADDR_FLAG));

    //clear addr flag
    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    //send data for len
    while(Len >0)
    {
        while( !I2C_GetFlagStatus(pI2CHandle -> pI2Cx, I2C_TXE_FLAG));
        pI2CHandle->pI2Cx->DR = *pTxbuffer;
        pTxbuffer++;
        Len--;

    }

    //wait for TXE=1 and BTF = 1 before stop

    while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TXE_FLAG));
    while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_BTF_FLAG));

    //generate stop
    I2C_GenerateStopCondition(pI2CHandle->pI2Cx);


}



