
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

typedef void (*IntCallBack_t) (void);

enum {
	// I2C_CR1 Register
	I2C_CR1_PE            = 0,   // Peripheral Enable
	I2C_CR1_SMBUS         = 1,   // SMBus Mode
	I2C_CR1_SMBTYPE       = 3,   // SMBus Type
	I2C_CR1_ENARP         = 4,   // ARP Enable
	I2C_CR1_ENPEC         = 5,   // PEC Enable
	I2C_CR1_ENGC          = 6,   // General Call Enable
	I2C_CR1_NOSTRETCH     = 7,   // Clock Stretching Disable (Slave mode)
	I2C_CR1_START         = 8,   // Start Generation
	I2C_CR1_STOP          = 9,   // Stop Generation
	I2C_CR1_ACK           = 10,  // Acknowledge Enable
	I2C_CR1_POS           = 11,  // Acknowledge/PEC Position
	I2C_CR1_PEC           = 12,  // Packet Error Checking
	I2C_CR1_ALERT         = 13,  // SMBus Alert
	I2C_CR1_SWRST         = 15,  // Software Reset

	// I2C_CR2 Register
	I2C_CR2_Freq0_5       = 0,
	I2C_CR2_ITERREN       = 8,
	I2C_CR2_ITEVTEN       = 9,
	I2C_CR2_ITBUFEN       = 10,
	I2C_CR2_DMAEN         = 11,
	I2C_CR2_LAST          = 12,

	// I2C_OAR1 Register
	I2C_OAR1_ADD0         = 0,   // Interface Address
	I2C_OAR1_ADD7_1       = 1,   // Interface Address
	I2C_OAR1_ADD8_9       = 8,   // Interface Address
	I2C_OAR1_ADDMODE      = 15,   // Interface Address

	// I2C_OAR2 Register
	I2C_OAR2_ENDUAL       = 0,   // Dual addressing mode enable
	I2C_OAR2_ADD2_7_1     = 1,   // Interface Address

	// I2C_DR Register
	I2C_DR_DR             = 0,   // Data Register

	// I2C_SR1 Register
	I2C_SR1_SB            = 0,   // Start Bit (Master mode)
	I2C_SR1_ADDR          = 1,   // Address Sent (Master mode)/Address Matched (Slave mode)
	I2C_SR1_BTF           = 2,   // Byte Transfer Finished
	I2C_SR1_ADD10         = 3,   // 10-bit header sent (Master mode)
	I2C_SR1_STOPF         = 4,   // Stop detection (Slave mode)
	I2C_SR1_RXNE          = 6,   // Data Register Not Empty (receive data register)
	I2C_SR1_TXE           = 7,   // Data Register Empty (transmit data register)
	I2C_SR1_BERR          = 8,   // Bus Error
	I2C_SR1_ARLO          = 9,   // Arbitration Lost (master mode)
	I2C_SR1_AF            = 10,  // Acknowledge Failure
	I2C_SR1_OVR           = 11,  // Overrun/Underrun
	I2C_SR1_PECERR        = 12,  // PEC Error in reception
	I2C_SR1_TIMEOUT       = 14,  // Timeout or Tlow Error
	I2C_SR1_SMBALERT      = 15,  // SMBus Alert

	// I2C_SR2 Register
	I2C_SR2_MSL           = 0,   // Master/Slave
	I2C_SR2_BUSY          = 1,   // Bus Busy
	I2C_SR2_TRA           = 2,   // Transmitter/Receiver
	I2C_SR2_GENCALL       = 4,   // General Call Address (Slave mode)
	I2C_SR2_SMBDEFAULT    = 5,   // SMBus Device Default Address (Slave mode)
	I2C_SR2_SMBHOST       = 6,   // SMBus Host Header (Slave mode)
	I2C_SR2_DUALF         = 7,   // Dual Flag (Slave mode)

	// I2C_CCR Register
	I2C_CCR_CCR           = 0,   // Clock Control Register
	I2C_CCR_MASTERMODE    = 15,   // Clock Control Register

	// I2C_TRISE Register
	I2C_TRISE_TRISE       = 0,   // Maximum Rise Time

	// I2C_FLTR Register
	I2C_FLTR_DNF          = 0,   // Digital Noise Filter
	I2C_FLTR_ANOFF        = 4,   // Analog Noise Filter OFF
};



#endif
