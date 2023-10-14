#ifndef 	SERIAL_CONTROL_HH_H
#define 	SERIAL_CONTROL_HH_H

#include "stdint.h"
#include "usart.h"

#define TX_BUFFER_SIZE 	100
#define RX_BUFFER_SIZE	100



typedef struct Rx_BufferTypedef
{
	uint8_t Data;
	char Rx_Buffer[RX_BUFFER_SIZE];
	uint16_t pWrite;
}Rx_BufferTypedef;

extern Rx_BufferTypedef GSM_Rx;
extern char Tx_Buffer[TX_BUFFER_SIZE];

void ClearRxBuffer(Rx_BufferTypedef *Type);
void ClearTxBuffer(void);
void SerialBegin(void);

#endif //SERIAL_CONTROL_HH_H

