
#include "STM32F446xx.h"
#include "DMA_prv.h"
#include "DMA_int.h"
#include "Utils.h"
#include "ErrType.h"

DMA_RegDef_t* DMAPeripheral [] = {DMA1, DMA2};

static void (*arrDMA1_PtrToFunction[8][Total_Number_Of_Interrupts])(void) = {NULL};
static void (*arrDMA2_PtrToFunction[8][Total_Number_Of_Interrupts])(void) = {NULL};

void DMA_vInit(DMA_HandleTypeDef_t* copy_eDMAConfig)
{
	DMA_vSetDMAStreamChannelSelection(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.Channel);
	DMA_vSetDMAStreamDataTransferDirection(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.Direction);
	DMA_vSetDMAMemoryIncrementMode(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.MINC);
	DMA_vSetDMAPeripheralIncrementMode(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.PINC);
	DMA_vSetDMACircularMode(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.CircularMode);
	DMA_vSetDMAStreamPriorityLevel(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.PriorityLevel);
	DMA_vSetDirectModeStatus(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.DirectOrFIFOMode);
	DMA_vSetFIFOThresholdSelection(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.FIFOThreshold);
	DMA_vSetDMAStreamMemoryBurstTransferSelection(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.MemoryBurst);
	DMA_vSetDMAStreamPeripheralBurstTransferSelection(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Init.PeripheralBurst);
	DMA_vSetTransferCompleteInterrupt(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->transfer_complete_interrupt_enable);
	DMA_vSetTransferErrorInterrupt(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->transfer_error_interrupt_enable);
	DMA_vSetFIFOErrorInterrupt(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->FIFO_error_interrupt_enable);
	DMA_vSetHalfTransferCompleteInterrupt(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->half_transfer_interrupt_enable);
	DMA_vSetDirectModeErrorInterrupt(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->direct_mode_error_interrupt_enable);
	DMA_vSetDMAStreamCurrentMemoryTarget(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->Current_memory_target);
	DMA_vSetDMAStreamDoubleBufferMode(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->double_buffer_mode);
	DMA_vSetDMAStreamIncreamentalOffset(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->peripheral_increment_offset_size);
	DMA_vSetDMAStreamMemorySize(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->MemorySIZE);
	DMA_vSetDMAStreamPeripheralSize(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->PeripheralSIZE);
	DMA_vSetDMAStreamPeripheralFlowController(copy_eDMAConfig->Init.DMANumber, copy_eDMAConfig->Init.Stream,copy_eDMAConfig->peripheral_flow_controller);

}
void DMA_vSetDMAStreamChannelSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,Channel_Selection_t copy_eChannel_Selection)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b111<<DMA_SxCR_CHSEL);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eChannel_Selection<<DMA_SxCR_CHSEL);
}
void DMA_vSetDMAStreamMemoryBurstTransferSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,M_P_Burst_Transfer_Configuration_t copy_eM_P_Burst_Transfer_Configuration)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b11<<DMA_SxCR_MBURST);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eM_P_Burst_Transfer_Configuration<<DMA_SxCR_MBURST);
}
void DMA_vSetDMAStreamPeripheralBurstTransferSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,M_P_Burst_Transfer_Configuration_t copy_eM_P_Burst_Transfer_Configuration)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b11<<DMA_SxCR_PBURST);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eM_P_Burst_Transfer_Configuration<<DMA_SxCR_PBURST);

}
void DMA_vSetDMAStreamCurrentMemoryTarget(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,Current_memory_target_t copy_Current_memory_target)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_CT);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_Current_memory_target<<DMA_SxCR_CT);

}
void DMA_vSetDMAStreamDoubleBufferMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,double_buffer_mode_t copy_double_buffer_mode)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_DBM);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_double_buffer_mode<<DMA_SxCR_DBM);

}
void DMA_vSetDMAStreamPriorityLevel(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,priority_level_t copy_epriority_level)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b11<<DMA_SxCR_PL);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_epriority_level<<DMA_SxCR_PL);

}
void DMA_vSetDMAStreamIncreamentalOffset(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,peripheral_increment_offset_size_t copy_eperipheral_increment_offset_size)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_PINCOS);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eperipheral_increment_offset_size<<DMA_SxCR_PINCOS);


}
void DMA_vSetDMAStreamMemorySize(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,P_M_SIZE_t copy_eP_M_SIZE)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b11<<DMA_SxCR_MSIZE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eP_M_SIZE<<DMA_SxCR_MSIZE);

}
void DMA_vSetDMAStreamPeripheralSize(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,P_M_SIZE_t copy_eP_M_SIZE)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b11<<DMA_SxCR_PSIZE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eP_M_SIZE<<DMA_SxCR_PSIZE);


}
void DMA_vSetDMAMemoryIncrementMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,Memory_Increment_Mode_t copy_eMemory_Increment_Mode)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_MINC);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eMemory_Increment_Mode<<DMA_SxCR_MINC);

}
void DMA_vSetDMAPeripheralIncrementMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,peripheral_Increment_Mode_t copy_peripheral_Increment_Mode)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_PINC);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_peripheral_Increment_Mode<<DMA_SxCR_PINC);

}
void DMA_vSetDMACircularMode(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,circular_mode_t copy_eCircular_mode)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_CIRC);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eCircular_mode<<DMA_SxCR_CIRC);

}
void DMA_vSetDMAStreamDataTransferDirection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,data_transfer_direction_t copy_edata_transfer_direction)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b11<<DMA_SxCR_DIR);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_edata_transfer_direction<<DMA_SxCR_DIR);


}
void DMA_vSetDMAStreamPeripheralFlowController(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,peripheral_flow_controller_t copy_eperipheral_flow_controller)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_PFCTRL);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_eperipheral_flow_controller<<DMA_SxCR_PFCTRL);

}
void DMA_vSetTransferCompleteInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,transfer_complete_interrupt_enable_t copy_etransfer_complete_interrupt_enable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_TCIE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_etransfer_complete_interrupt_enable<<DMA_SxCR_TCIE);


}
void DMA_vSetHalfTransferCompleteInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,half_transfer_interrupt_enable_t half_transfer_interrupt_enable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_HTIE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (half_transfer_interrupt_enable<<DMA_SxCR_HTIE);

}
void DMA_vSetTransferErrorInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,transfer_error_interrupt_enable_T copy_etransfer_error_interrupt_enable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_TEIE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_etransfer_error_interrupt_enable<<DMA_SxCR_TEIE);

}
void DMA_vSetDirectModeErrorInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,direct_mode_error_interrupt_enable_t copy_edirect_mode_error_interrupt_enable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_DMEIE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_edirect_mode_error_interrupt_enable<<DMA_SxCR_DMEIE);

}
void DMA_vEnableStream(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection, stream_enable_t copy_estream_enable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR &=~ (0b1<<DMA_SxCR_EN);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxCR |= (copy_estream_enable<<DMA_SxCR_EN);

}
void DMA_vSetNumberOfDataToBeTransefered(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint16_t copy_u16NumberOfData)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxNDTR = (copy_u16NumberOfData<<0);

}
void DMA_vSetAddressOfPeripheral(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint32_t copy_u32AddressOfPeripheral)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxPAR = (copy_u32AddressOfPeripheral<<0);

}
void DMA_vSetAddressOfMemory0(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint32_t copy_u32AddressOfMemory0)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxM0AR = (copy_u32AddressOfMemory0<<0);

}
void DMA_vSetAddressOfMemory1(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,uint32_t copy_u32AddressOfMemory1)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxM1AR = (copy_u32AddressOfMemory1<<0);

}
void DMA_vSetFIFOErrorInterrupt(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,FIFO_error_interrupt_enable_t copy_eFIFO_error_interrupt_enable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxFCR &=~ (0b1<<DMA_SxFCR_FEIE);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxFCR |= (copy_eFIFO_error_interrupt_enable<<DMA_SxFCR_FEIE);

}
//uint8_t DMA_u8GetFIFOStatus();
void DMA_vSetDirectModeStatus(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,direct_mode_disable_t copy_edirect_mode_disable)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxFCR &=~ (0b1<<DMA_SxFCR_DMDIS);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxFCR |= (copy_edirect_mode_disable<<DMA_SxFCR_DMDIS);


}
void DMA_vSetFIFOThresholdSelection(DMA_Peripheral_Number_t copy_eDMA_Peripheral_Number, Stream_Selection_t copy_eStream_Selection,FIFO_threshold_t copy_eFIFO_threshold)
{
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxFCR &=~ (0b11<<DMA_SxFCR_FTH);
	DMAPeripheral[copy_eDMA_Peripheral_Number]->DMA_STREAM[copy_eStream_Selection].DMA_SxFCR |= (copy_eFIFO_threshold<<DMA_SxFCR_FTH);

}


void DMA_vStart(DMA_HandleTypeDef_t* copy_eDMAConfig,uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	if (copy_eDMAConfig->Init.Direction == memory_to_peripheral)
	{
		DMA_vSetAddressOfMemory0(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,SrcAddress);
		DMA_vSetAddressOfPeripheral(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,DstAddress);

	}
	else
	{
		DMA_vSetAddressOfMemory0(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,DstAddress);
		DMA_vSetAddressOfPeripheral(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,SrcAddress);

	}
	DMA_vSetNumberOfDataToBeTransefered(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,DataLength);
	DMA_vEnableStream(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,stream_enabled);


}
void DMA_vStart_IT(DMA_HandleTypeDef_t* copy_eDMAConfig,uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	if (copy_eDMAConfig->Init.Direction == memory_to_peripheral)
	{
		DMA_vSetAddressOfMemory0(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,SrcAddress);
		DMA_vSetAddressOfPeripheral(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,DstAddress);

	}
	else
	{
		DMA_vSetAddressOfMemory0(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,DstAddress);
		DMA_vSetAddressOfPeripheral(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,SrcAddress);

	}
	DMA_vSetNumberOfDataToBeTransefered(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,DataLength);
	DMA_vSetTransferCompleteInterrupt(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,TC_interrupt_enabled);

	DMA_vEnableStream(copy_eDMAConfig->Init.DMANumber,copy_eDMAConfig->Init.Stream,stream_enabled);


}
void DMA_vReadFlagStatus(DMA_Peripheral_Number_t DMA_Number,Stream_Selection_t Stream_Number,DMA_Interrupt_t copy_eDMA_Interrupt,uint8_t *interruptStatusFlag)
{

	uint8_t flagShift=(uint8_t)copy_eDMA_Interrupt+6*(((uint8_t)Stream_Number%4))+(((((uint8_t)Stream_Number%4))/2)*4);
	*interruptStatusFlag= READ_BIT(DMAPeripheral[DMA_Number]->DMA_LISR[Stream_Number/4],flagShift );

}
void DMA_vClearFlagStatus(DMA_Peripheral_Number_t DMA_Number,Stream_Selection_t Stream_Number,DMA_Interrupt_t copy_eDMA_Interrupt)
{
	uint8_t flagShift=(uint8_t)copy_eDMA_Interrupt+6*(((uint8_t)Stream_Number%4))+(((((uint8_t)Stream_Number%4))/2)*4);
    SET_BIT(DMAPeripheral[DMA_Number]->DMA_LIFCR[Stream_Number/4],flagShift );

}

void DMA_vIRQHandler(DMA_Peripheral_Number_t DMA_Number,Stream_Selection_t Stream_Number)
{

	uint8_t flagStatus=0;
	for (uint8_t i=0 ;i<Total_Number_Of_Interrupts ; i++)
	{

		DMA_vReadFlagStatus(DMA_Number,Stream_Number, i, &flagStatus);
		if (flagStatus)
		{
			switch (DMA_Number)
			{
			case DMA_Number_1:
				if (arrDMA1_PtrToFunction[Stream_Number][i] != NULL)
				{
					DMA_vClearFlagStatus(DMA_Number,Stream_Number,i);

					arrDMA1_PtrToFunction[Stream_Number][i]();
				}
				break;
			case DMA_Number_2:
				if (arrDMA2_PtrToFunction[Stream_Number][i] != NULL)
				{
					DMA_vClearFlagStatus(DMA_Number,Stream_Number,i);

					arrDMA2_PtrToFunction[Stream_Number][i]();
				}
				break;
			default:
				/* Do Nothing!*/
				break;
			}
			// clear flag after interrupt served

		}
		else
		{
			/* Do Nothing!*/
		}
	}

}

void DMA_vSetCallBack(DMA_HandleTypeDef_t* copy_eDMAConfig,DMA_Interrupt_t copy_eDMA_Interrupt, void (*PtrToFunc)(void))
{
	switch (copy_eDMAConfig->Init.DMANumber)
	{
	case DMA_Number_1:
		arrDMA1_PtrToFunction[copy_eDMAConfig->Init.Stream][copy_eDMA_Interrupt]=PtrToFunc;
		break;
	case DMA_Number_2:
		arrDMA2_PtrToFunction[copy_eDMAConfig->Init.Stream][copy_eDMA_Interrupt]=PtrToFunc;
		break;
	default :
		break;
	}

}

/* ==========================
 *           DMA1
 * ========================== */

void DMA1_Stream0_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_0);
}
void DMA1_Stream1_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_1);
}
void DMA1_Stream3_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_3);
}
void DMA1_Stream4_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_4);
}
void DMA1_Stream5_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_5);
}
void DMA1_Stream6_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_6);
}
void DMA1_Stream7_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_1,Stream_7);
}

/* ==========================
 *           DMA2
 * ========================== */

void DMA2_Stream0_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_0);
}
void DMA2_Stream1_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_1);
}
void DMA2_Stream2_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_2);
}
void DMA2_Stream3_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_3);
}
void DMA2_Stream4_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_4);
}
void DMA2_Stream5_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_5);
}
void DMA2_Stream6_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_6);
}
void DMA2_Stream7_IRQHandler(void)
{
	DMA_vIRQHandler(DMA_Number_2,Stream_7);
}
