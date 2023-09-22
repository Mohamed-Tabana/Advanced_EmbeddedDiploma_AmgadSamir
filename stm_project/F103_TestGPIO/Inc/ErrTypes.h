/*
 * ErrTypes.h
 *
 *  Created on: May 10, 2023
 *      Author: mhmd wael
 */

#ifndef INC_ERRTYPES_H_
#define INC_ERRTYPES_H_

typedef enum  {  NOK , OK ,Null_Pointer,InvalidPORTPIN
					,SPI_WRONG_TRANSFER_MODE
					,SPI_WRONG_SLAVE_MANAGE_STATE
					,SPI_WRONG_FRAME_TYPE
					,SPI_WRONG_FRAME_SIZE
					,SPI_WRONG_CLOCK_POLARITY
					,SPI_WRONG_CLOCK_PHASE
					,SPI_WRONG_CHIP_MODE
					,SPI_WRONG_CRC_STATE
					,SPI_WRONG_BAUDRATE
					,SPI_WRONG_MULTIMASTER_STATE
					,SPI_WRONG_SPI_NUMBER
					,WRONG_SLAVE_STATE}Error_State_t;

#define NULL ((void *)0)
#define FLAG_RESET		0
#define FLAG_SET		1


#endif /* INC_ERRTYPES_H_ */
