#include "Quectel_GSM_hh.h"
#include "SerialControl_hh.h"
#include "PinMap_hh.h"

uint8_t Quectel_StateMachine_xdu8 = 0;

extern QuectelGsm MQTT;

void QuectelGsm::Quectel_Init(void)
{
	ClearRxBuffer(&GSM_Rx);
	SendString("ATE0\r\n"); // Disable Echo ->OK
	WaitReturn("OK",1000);
	ClearRxBuffer(&GSM_Rx);
	
	SendString("AT&W\r\n"); //  Save setting command ->OK
	WaitReturn("OK",1000);
	ClearRxBuffer(&GSM_Rx);
}

QuectelGsm::QuectelGsm(void)
{
}
QuectelGsm::QuectelGsm(const char *host_name, uint32_t port,const char *username, const char *password,uint8_t tcpconnectID,const char *clientID)
{
	this->_host_name = host_name;
	this->_port = port;
	this->_username = username;
	this->_password = password;
	this->_tcpconnectID =tcpconnectID;
	this->_clientID= clientID;
}

void QuectelGsm::SendString(const char *string)
{
		HAL_UART_Transmit(&huart1,(uint8_t*)string,strlen(string),1000);
}
void QuectelGsm::PowerUp(void)
{
	SendString("ATE0\r\n");
	if(WaitReturn("OK",1000)!=WAIT_OK)
	{
		HAL_GPIO_WritePin(MC60_PWRKEY_PORT,MC60_PWRKEY_PIN,GPIO_PIN_SET);
		HAL_Delay(2500);
		HAL_GPIO_WritePin(MC60_PWRKEY_PORT,MC60_PWRKEY_PIN,GPIO_PIN_RESET);
		HAL_Delay(5000);
	}
	else
	{
		// Do nothing
	}
}
WaitReturn_Typedef QuectelGsm::WaitReturn(const char *command, uint32_t Timeout)
{
	uint32_t Tickstart = 0U;	
	uint8_t length = strlen(command);	
	char *pt;
	
	Tickstart = HAL_GetTick();
	while(strncmp(pt,command,length) != 0) // Wait untill Rx data have command data
	{
		if((HAL_GetTick() - Tickstart ) >= Timeout)
		{
			return WAIT_TIME_OUT;
		}	
		pt =strstr((char*)GSM_Rx.Rx_Buffer ,command);
	}
	return WAIT_OK;		
}


bool QuectelGsm::openNetwork()
{
	return openNetwork(this->_tcpconnectID,this->_host_name,this->_port);
}
bool QuectelGsm::openNetwork(uint8_t tcpconnectID, const char *host_name, uint16_t port)
{
	snprintf(Tx_Buffer,TX_BUFFER_SIZE, "%s%d%s%s%s%d%s",
	"AT+QMTOPEN=",tcpconnectID,",\"",host_name,"\",\"",port,"\"\r\n");
	
	SendString(Tx_Buffer); 
	WaitReturn("OK",5000);
	
	if(WaitReturn("+QMTOPEN:",5000)==WAIT_OK)
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return true;
	}
	else
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return false;
	}
}


bool QuectelGsm::connectServer()
{
	connectServer(this->_tcpconnectID,this->_clientID,this->_username,this->_password);
	return 1;
}

bool QuectelGsm::connectServer(uint8_t tcpconnectID, const char *clientID, const char *username, const char *password)
{
		snprintf(Tx_Buffer,TX_BUFFER_SIZE, "%s%d%s%s%s%s%s%s%s",
	"AT+QMTCONN=",tcpconnectID,",\"",clientID,"\",\"",username,"\",\"",password,"\"\r\n");
	
	SendString(Tx_Buffer); 
	WaitReturn("OK",5000);
	if(WaitReturn("+QMTCONN:",5000)==WAIT_OK)
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return true;
	}
	else
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return false;
	}
}

bool QuectelGsm::subscribe(uint16_t msgID, const char *topic, uint8_t qos)
{
	return subscribe(this->_tcpconnectID,msgID, topic, qos);
}
bool QuectelGsm::subscribe( uint16_t msgID, const char *topic)
{
	return subscribe(this->_tcpconnectID,msgID, topic, 1);
}

bool QuectelGsm::subscribe(uint8_t tcpconnectID, uint16_t msgID, const char *topic, uint8_t qos)
{
		snprintf(Tx_Buffer,TX_BUFFER_SIZE, "%s%d%s%d%s%s%s%d%s",
	"AT+QMTSUB=",tcpconnectID,",",msgID,",\"",topic,"\",", qos ,"\r\n");
	
	SendString(Tx_Buffer); 
	WaitReturn("OK",3000);
	if(WaitReturn("+QMTSUB:",5000)==WAIT_OK)
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return true;
	}
	else
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return false;
	}
}

bool QuectelGsm::publish( uint16_t msgID, uint8_t qos, uint8_t retain,
	const  char *topic, uint8_t size,const  char *payload)
{
	return publish(this->_tcpconnectID,msgID, qos,retain,topic,size,payload);
}
bool QuectelGsm::publish(uint16_t msgID,const char *topic,const char *payload)
{
	uint16_t length = strlen(payload);
	return publish(this->_tcpconnectID,msgID,1,0,topic,length,payload);
}
bool QuectelGsm::publish(uint8_t tcpconnectID, uint16_t msgID, uint8_t qos,
	uint8_t retain,const char *topic, uint8_t size,const char *payload)
{
		snprintf(Tx_Buffer,TX_BUFFER_SIZE, "%s%d%s%d%s%d%s%d%s%s%s%d%s",
	"AT+QMTPUB=",tcpconnectID,",",msgID,",",qos,",",retain,",\"",topic,"\",", size ,"\r\n");
	
	SendString(Tx_Buffer); 
	HAL_Delay(1000);
	SendString(payload); //  Publish a topic
	
	if(WaitReturn("+QMTPUB:",5000)==WAIT_OK)
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return true;
	}
	else
	{
		ClearRxBuffer(&GSM_Rx);
		ClearTxBuffer();
		return false;
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	GSM_Rx.Rx_Buffer[GSM_Rx.pWrite++] =GSM_Rx.Data;
	if(GSM_Rx.pWrite >= RX_BUFFER_SIZE)
	{
		GSM_Rx.pWrite=0;
	}
	else
	{
		//MQTT.onMessageCallBack(topic;payload);		
	}
}

