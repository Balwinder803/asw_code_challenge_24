
/**
  ******************************************************************************
  * @file           : lis3mdltr_driver.c
  * @author         : Balwinder singh
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/*****************************Include header files*****************************/
#include "lis3mdltr_driver.h"



/*****************************Public functions  *******************************/
status_t lis3mdltr_chipInit()
{
    status_t status = STATUS_ERROR;
    uint8_t rxBuff;
    
    if( LIS3MDLTR_DEFAULT_VALUE == i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_DUMMY_REGISTER, 1u, &rxBuff) )
    {
        status = STATUS_OK;
    }
    return status;
    
}



status_t lis3mdltr_GetFullScaleConfig(lis3mdltr_driver_FullScaleConfig_t *readConfig)
{
    status_t status = STATUS_ERROR;
    uint8_t rxBuff;
    
    if(STATUS_OK == i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_CTRL_REG2, 1u, &rxBuff))
    {
        uint8_t regValue = (rxBuff & LIS3MDLTR_FULL_SCALE_CONFIG_MASK) >> FIVE;
        switch(regValue)
        {
        case 0x00:
            *readConfig = FOUR_GAUSS;
            break;
        case 0x01:
            *readConfig = EIGHT_GAUSS;
            break;
        case 0x02:
            *readConfig = TWELVE_GAUSS;
            break;
        case 0x03:
            *readConfig = SIXTEEN_GAUSS;
            break;
        default:
            *readConfig = INVALID;
            break;
    }

    
    return status;
}


status_t lis3mdltr_GetDataRate(lis3mdltr_driver_DataRateSel_t *operatingDateRate)
{
    status_t status = STATUS_ERROR;
    uint8_t rxBuff;

    if(STATUS_OK == i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_CTRL_REG1, 1u, &rxBuff))
    {
        uint8_t maskValue = (rxBuff & LIS3MDLTR_DATA_RATE_MASK) >> TWO;
        switch(maskValue)
       {
       case 0x00:
            *operatingDateRate  = OUT_DATA_RATE_0_625_Hz;
            break;
        case 0x01:
            *operatingDateRate  = OUT_DATA_RATE_1_25_Hz;
            break;
        case 0x02:
            *operatingDateRate  = OUT_DATA_RATE_2_25_Hz;
            break;
        case 0x03:
            *operatingDateRate  = OUT_DATA_RATE_5_Hz;
            break;
        case 0x04:
            *operatingDateRate  = OUT_DATA_RATE_10_Hz;
            break;
        case 0x05:
            *operatingDateRate  = OUT_DATA_RATE_20_Hz;
            break;
        case 0x06:
            *operatingDateRate  = OUT_DATA_RATE_40_Hz;
            break;
        case 0x07:
            *operatingDateRate  = OUT_DATA_RATE_80_Hz;
            break;
        default:
            *operatingDateRate = INVALID;
            break;
        }
    }

    return status;
}



status_t lis3mdltr_SetDataRate(lis3mdltr_driver_DataRateSel_t dataRate)
{
    uint8_t rxBuff = 0;
    status_t status = STATUS_ERROR;
    //Read the entire control register 1 and only change data rate bits
    if(STATUS_OK == i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_CTRL_REG1, 1u, &rxBuff))
    { 
        rxBuff = rxBuff & 0xE1; //   clear data rate bits 
        dataRate = (dataRate << 2) & LIS3MDLTR_DATA_RATE_MASK ;
        uint8_t txBuff = rxBuff  | dataRate ;
        status = i2c_write(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_CTRL_REG1, 1u, &txBuff);
	}
    return status;
}

status_t lis3mdltr_SetInterruptPin(lis3mdltr_interupt_pin_state_t setPinState)
{
    uint8_t rxBuff;
// Read default status of interupt pin

    status_t status = i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_ITR_CFG, 1u, &rxBuff);

    if (status == STATUS_OK)
    {
        lis3mdltr_interupt_pin_state_t pinCurrentStatus = (lis3mdltr_interupt_pin_state_t)(rxBuff & 0x01);

        if (setPinState != pinCurrentStatus )
        {
            rxBuff = (uint8_t)setPinState;
            status = i2c_write(LIS3MDLTR_I2C_BUS_ADDRESS, LIS3MDLTR_ITR_CFG, 1u, &rxBuff);
        }
    }

    return status;
}

status_t lis3mdltr_ReadAxisData(lis3mdltr_driver_Axis_t readAxis, int16_t *rxBuff)
{
    uint8_t readAddr = 0;
    uint8_t readAxisLowValue = 0, readAxisHighValue = 0;
    status_t status = STATUS_ERROR;


    switch (readAxis) {
        case READ_X_AXIS:
            readAddr = OUTPUT_X_AXIS_LOW_ADDR;
            break;
        case READ_Y_AXIS:
            readAddr = OUTPUT_Y_AXIS_LOW_ADDR;
            break;
        case READ_Z_AXIS:
            readAddr = OUTPUT_Z_AXIS_LOW_ADDR;
            break;
        default:
            return status;
    }

    status = i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, readAddr, 1u, &readAxisLowValue);
    status = i2c_read(LIS3MDLTR_I2C_BUS_ADDRESS, readAddr + 1, 1u, &readAxisHighValue);

    if (status == STATUS_OK)
    {
        *rxBuff = (int16_t)((readAxisHighValue << 8) | readAxisLowValue);
    }

    return status;
}
