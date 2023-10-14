#ifndef QUECTEL_GSM_HH_H
#define QUECTEL_GSM_HH_H
#include "SerialControl_hh.h"
#include "stdint.h"
#include "usart.h"
#include "gpio.h"
#include <string>
using namespace std;


extern uint8_t Quectel_StateMachine_xdu8;

typedef enum
{
	WAIT_OK = 1,
	WAIT_TIME_OUT = 2
} WaitReturn_Typedef;

typedef enum
{
	GSM,
	GPS
} UART_ModuleType;

class QuectelGsm
{
private:
	const char *_host_name;
	uint32_t _port;
	const char *_username;
	const char *_password;
	uint8_t _tcpconnectID;
	const char *_clientID;
protected:
	
public:

	QuectelGsm(void);
	QuectelGsm(const char *host_name, uint32_t port,const char *username,
		const char *password,uint8_t tcpconnectID,const char *clientID);

	bool openNetwork(uint8_t tcpconnectID,const char *host_name, uint16_t port);
	bool openNetwork();

	bool connectServer(uint8_t tcpconnectID,const char *clientID,const char *username,const char *password);
	bool connectServer();	

	bool subscribe(uint8_t tcpconnectID, uint16_t msgID,const char *topic, uint8_t qos);
	bool subscribe(uint16_t msgID, const char *topic, uint8_t qos);
	bool subscribe(uint16_t msgID,const  char *topic);

	bool publish(uint8_t tcpconnectID, uint16_t msgID, uint8_t qos, uint8_t retain,
		const char *topic, uint8_t size, const char *payload);
	bool publish(uint16_t msgID, uint8_t qos, uint8_t retain,const char *topic, uint8_t size,const char *payload);
	bool publish(uint16_t msgID,const char *topic,const char *payload);

	void onMessageCallBack(const char *topic,const char *payload);

	void SendString(const char *string);
	void PowerUp(void);
	WaitReturn_Typedef WaitReturn(const char *command, uint32_t Timeout);
	void Quectel_Init(void);
};
#endif //QUECTEL_MC60_HH_H
