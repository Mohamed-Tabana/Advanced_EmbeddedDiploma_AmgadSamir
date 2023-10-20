#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "DMA_int.h"
#include "I2C_prv.h"
#include "stdint.h"
#include "STM32F446xx.h"
#include "Utils.h"
#include "DMA_int.h"

typedef enum {
	I2C_Channel_1=0,
	I2C_Channel_2,
	I2C_Channel_3,
} I2C_Peripheral_Channel;

typedef enum {
	I2C_Peripheral_DISABLE=0,                // Peripheral Enable: Enabled
	I2C_Peripheral_EN=1,           // Peripheral Enable: Disabled
} I2C_Peripheral_Enable;

typedef enum {
    I2C_SMBUS_I2C = 0,             // SMBus Mode: I2C
    I2C_SMBUS_SMBus,               // SMBus Mode: SMBus
} I2C_SMBus_Mode;

typedef enum {
    I2C_SMBTYPE_Device = 0,        // SMBus Type: Device
    I2C_SMBTYPE_Host,              // SMBus Type: Host
} I2C_SMBTYPE;

typedef enum {
    I2C_ENARP_Disabled = 0,        // ARP Enable: Disabled
    I2C_ENARP_Enabled,             // ARP Enable: Enabled
} I2C_ARP_Enable;

typedef enum {
    I2C_ENPEC_Disabled = 0,        // PEC Enable: Disabled
    I2C_ENPEC_Enabled,             // PEC Enable: Enabled
} I2C_PEC_Enable;
typedef enum {
    I2C_ENGC_Disabled = 0,         // General Call Enable: Disabled
    I2C_ENGC_Enabled,              // General Call Enable: Enabled
} I2C_General_Call_Enable;

typedef enum {
    I2C_CLK_STRETCH_Enabled = 0,     // Clock Stretching Disable (Slave mode): Enabled
    I2C_CLK_STRETCH_Disabled,        // Clock Stretching Disable (Slave mode): Disabled
} I2C_STRETCH_Enable;

typedef enum {
    I2C_START_NoStart = 0,         // Start Generation: No Start
    I2C_START_Start,               // Start Generation: Start
} I2C_START_Generation;

typedef enum {
    I2C_STOP_NoStop = 0,           // Stop Generation: No Stop
    I2C_STOP_Stop,                 // Stop Generation: Stop
} I2C_STOP_Generation;

typedef enum {
    I2C_ACK_Disabled = 0,          // Acknowledge Enable: Disabled
    I2C_ACK_Enabled,               // Acknowledge Enable: Enabled
} I2C_ACK_Enable;

typedef enum {
    I2C_POS_Current = 0,           // Acknowledge/PEC Position: Current
    I2C_POS_Next,                  // Acknowledge/PEC Position: Next
} I2C_POS_Options;

typedef enum {
    I2C_PEC_Disabled = 0,          // Packet Error Checking: Disabled
    I2C_PEC_Enabled,               // Packet Error Checking: Enabled
} I2C_PEC_Options;

typedef enum {
    I2C_ALERT_NoAlert = 0,         // SMBus Alert: No Alert
    I2C_ALERT_Alert,               // SMBus Alert: Alert
} I2C_ALERT_Options;

typedef enum {
    I2C_SWRST_NotUnderReset = 0,   // Software Reset: Not under reset state
    I2C_SWRST_UnderReset,          // Software Reset: Under reset state
} I2C_SWRESET;

typedef enum {
    I2C_Interrupt_Disable = 0,
	I2C_Interrupt_Enable,
} I2C_InterruptEnable;

typedef enum {
    I2C_DMA_Disable = 0,
	I2C_DMA_Enable,
} I2C_DMAEnable;

typedef enum {
    I2C_Next_Is_Not_Last = 0,
	I2C_Next_Is_Last,
} I2C_DMALastTransfer;

typedef enum {
    I2C_7_bit = 0,
	I2C_10_bit,
} I2C_Addressing_Mode;

typedef enum {
    I2C_Dual_AM_Disable = 0,
	I2C_Dual_AM_Enable,
} I2C_Dual_Addressing_Mode;

typedef enum {
	I2C_FLAG_START_CONDITION_SB,
	I2C_FLAG_ADDRESS_SENT_ADDR,
	I2C_BYTE_TRANSFER_FINISHED_BTF,
	I2C_FLAG_STOP_CONDITION_STOBF=4,
	I2C_FLAG_DATA_REG_FULL_RxNE=6,
	I2C_FLAG_DATA_REG_EMPTY_TxE,
	I2C_FLAG_DATA_BUS_ERROR_BERR,
	I2C_FLAG_ARBITRATION_LOST_ARLO,
	I2C_FLAG_ACK_FAILURE_AF,
	I2C_FLAG_OVER_RUN_OVR,
	I2C_FLAG_PEC_RECEPTION_PECERR,

	// Here subtract 32 for >31 flags I2C_SR2
	I2C_FLAG_MASTER_SLAVE_MSL=32,
	I2C_FLAG_BUS_BUSY_BUSY=33,
	I2C_FLAG_TRANSMITTER_RECEIVER_TRA=34,
	I2C_FLAG_GENERAL_CALL_GENCALL=36,

} I2C_Status_Flags;

typedef enum {
    I2C_SM_MODE = 0,
	I2C_FM_MODE,
} I2C_Select_Master_Mode;

typedef struct {
	I2C_Peripheral_Channel I2C_ID;
	I2C_Select_Master_Mode I2C_MasterMode;
	I2C_STRETCH_Enable I2C_StretchClk;
	uint8_t I2C_InterfaceAddress ;
} I2C_HandleTypeDef_t;

void I2C_vInit(I2C_HandleTypeDef_t* hi2c);
void I2C_SendDataToSlaveSynch(I2C_HandleTypeDef_t* hi2c, uint8_t copy_u8SlaveAdd,uint8_t copy_u8DataLength,uint8_t* copy_pu8Data);
/*
 * @brief: this function is used only for receiving Data >2
 *
 * */
void I2C_RequestDataFromSlaveSynch(I2C_HandleTypeDef_t* hi2c, uint8_t copy_u8SlaveAdd,uint8_t copy_u8DataLength,uint8_t* copy_pu8Data);
void I2C_SendDataToSlave_DMA(I2C_HandleTypeDef_t* hi2c, DMA_HandleTypeDef_t* copy_eDMAConfig,uint8_t copy_u8SlaveAdd,uint32_t copy_u32DataLength,uint8_t* copy_pu8Data);
void I2C_ReceiveDataFromSlave_DMA(I2C_HandleTypeDef_t* hi2c, DMA_HandleTypeDef_t* copy_eDMAConfig,uint8_t copy_u8SlaveAdd,uint32_t copy_u32DataLength,uint8_t* copy_pu8Data);





#endif
