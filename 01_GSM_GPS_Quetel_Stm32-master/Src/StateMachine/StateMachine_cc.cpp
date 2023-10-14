#include "StateMachine_hh.h"
#include "Quectel_GSM_hh.h"
#include "ArduinoJson.h"
#include "MqttConfig_hh.h"

uint8_t App_StateMachine_xdu8 = 0;

void StateMachine(void)
{
  StaticJsonDocument<200> doc;
  doc["VoltV1N"]  = 200 ;
  doc["VoltV2N"]  = 220;
  doc["VoltV3N"]  = 221;
  doc["AverVolt"] =	600;
  doc["VoltV12"]  = 600;
  doc["VoltV23"]  =	600;
  doc["VoltV31"]  =	650;
  doc["CurrI1"]   = 10;
  doc["CurrI2"]   =	47;
  doc["CurrI3"]   = 67;
	QuectelGsm Gsm(HostName,Port,UserName,Password,TcpId,ClientID);
	switch(App_StateMachine_xdu8)
	{
		case	STATE_INIT:			
			App_StateMachine_xdu8 = STATE_READY;
			break;
		case	STATE_READY:
			char JSONmessageBuffer[500];
			serializeJson(doc, JSONmessageBuffer);
			SerialBegin();
		
			Gsm.PowerUp();
			Gsm.Quectel_Init();
			Gsm.openNetwork();
			Gsm.connectServer();
			//Gsm.subscribe(1,"demo1");
			Gsm.publish(1,"demo1",(const char *)JSONmessageBuffer);
			App_StateMachine_xdu8 = STATE_ERROR;
			break;
		case	STATE_ERROR:				
			break;
		default:	
			break;
				
	}
}
