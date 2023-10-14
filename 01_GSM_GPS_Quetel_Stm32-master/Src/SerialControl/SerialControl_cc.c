#include "SerialControl_hh.h"
#include "Quectel_GSM_hh.h"

char Tx_Buffer[TX_BUFFER_SIZE];
Rx_BufferTypedef GSM_Rx;


void ClearRxBuffer(Rx_BufferTypedef *Type)
{
	for(uint8_t i=0; i< RX_BUFFER_SIZE; i++)
	{
		Type->Rx_Buffer[i]=0;
	}
	Type->Data=0;
	Type->pWrite=0;
}

void ClearTxBuffer(void)
{
	for(uint8_t i=0; i< TX_BUFFER_SIZE; i++)
	{
		Tx_Buffer[i]=0;
	}
}

void SerialBegin(void)
{
	HAL_UART_Receive_DMA(&huart1,&GSM_Rx.Data ,1);
}

 
