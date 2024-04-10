
/**
  ******************************************************************************
  * @file           : lis3mdltr_driver.h
  * @author         : Balwinder singh
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/*****************************Include header files*****************************/

#include <stdlib.h>
#include <i2c.h>

/******************************************************************************
                                Macro's
 ******************************************************************************/

#define LIS3MDLTR_DUMMY_REGISTER            0x0F
#define LIS3MDLTR_DEFAULT_VALUE             0x3D
#define LIS3MDLTR_I2C_BUS_ADDRESS           0x50

// Masking values
#define LIS3MDLTR_FULL_SCALE_CONFIG_MASK    0x60
#define LIS3MDLTR_DATA_RATE_MASK            0x1C
#define LIS3MDLTR_OPERATION_MODE_MASK       0x60
#define LIS3MDLTR_FAST_ODR_MASK             0x02

/**************** Control register **********************/
#define LIS3MDLTR_CTRL_REG1                 0x20
#define LIS3MDLTR_CTRL_REG2                 0x21


/**************** OUTPUT register **********************/
#define OUTPUT_X_AXIS_LOW_ADDR             0x28
#define OUTPUT_Y_AXIS_LOW_ADDR             0x2A
#define OUTPUT_Z_AXIS_LOW_ADDR             0x2C
#define LIS3MDLTR_ITR_CFG                  0x30

/******************************************************************************
                                Structure and enums
 ******************************************************************************/
typedef enum {
    ONE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
}hardcode_values_t


typedef enum {
    DISABLE = 0,
    ENABLE,
}lis3mdltr_interupt_pin_state_t;

typedef enum {
    OUT_DATA_RATE_0_625_Hz = 0,
    OUT_DATA_RATE_1_25_Hz,
    OUT_DATA_RATE_2_25_Hz,
    OUT_DATA_RATE_5_Hz,
    OUT_DATA_RATE_10_Hz,
    OUT_DATA_RATE_20_Hz,
    OUT_DATA_RATE_40_Hz,
    OUT_DATA_RATE_80_Hz,
    INVALID,
} lis3mdltr_driver_DataRateSel_t;

typedef enum {
    FOUR_GAUSS = 0,
    EIGHT_GAUSS,
    TWELVE_GAUSS,
    SIXTEEN_GAUSS,
    INVALID,
} lis3mdltr_driver_FullScaleConfig_t;

typedef enum {
    LOW_POWER_MODE = 0,
    MEDIUM_PERFORMANCE_MODE,
    HIGH_PERFORMANCE_MODE,
    ULTRA_HIGH_PERFORMANCE_MODE,
    INVALID,
} lis3mdltr_driver_OperatingMode_t;

typedef enum {
    READ_X_AXIS,
    READ_Y_AXIS,
    READ_Z_AXIS,
    INVALID,
} lis3mdltr_driver_Axis_t;


/*****************************Public functions prototypes  *******************************/


/**
 * @brief Init a chip and verify communication.
 * @param[input] none.
 * @param[output] none.
 *
 * @return STATUS_OK if successful.
 */
status_t lis3mdltr_chipInit(void);
/**
 * @brief This function reads the full scale configuration from chip.
 * @param[input] none.
 * @param[output] readConfig : It hold the read values .
 *
 * @return STATUS_OK if successful.
 */
status_t lis3mdltr_GetFullScaleConfig(lis3mdltr_driver_FullScaleConfig_t *readConfig);
/**
 * @brief This function used to change the state of interupt pin.
 * @param[input] setPinState : state to be set for interupt pin.
 * @param[output] none.
 *
 * @return STATUS_OK if successful.
 */
status_t lis3mdltr_SetInterruptPin(lis3mdltr_interupt_pin_state_t setPinState);
/**
 * @brief This function use to fetch the data rate .
 * @param[input] none.
 * @param[output] operatingDateRate. : It stores the read data
 *
 * @return STATUS_OK if successful.
 */
status_t lis3mdltr_GetDataRate(lis3mdltr_driver_DataRateSel_t *operatingDateRate);
/**
 * @brief This function allow user to set the desired datarate.
 * @param[input] operatingModes : Contain data rate value to be set.
 * @param[output] none.
 *
 * @return STATUS_OK if successful.
 */
status_t lis3mdltr_SetDataRate(lis3mdltr_driver_DataRateSel_t dataRate);
/**
 * @brief This function reads the output values for specified axis.
 * @param[input] readAxis: it tells the information about the axis value to be read.
 * @param[output] rxBuff: contain the read value for axis.
 *
 * @return STATUS_OK if successful.
 */
status_t lis3mdltr_ReadAxisData(lis3mdltr_driver_Axis_t readAxis, int16_t *rxBuff);