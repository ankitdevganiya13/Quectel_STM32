#ifndef ZIGBEE_WEBEE_HH_H
#define ZIGBEE_WEBEE_HH_H

#include "stdint.h"
#include "SerialControl_hh.h"

#define TRANSMIT_BUFFER_SIZE 255

typedef enum
{
  COORDINATOR = 0x00,
  ROUTER = 0x01,
  END_DEVICE = 0x02,
} ZigbeeRole_Typedef;

typedef enum
{
  BROADCAST = 0x00,
  MULTICAST = 0x01,
  UNICAST = 0x02,
} TransmitMethod_Typedef;

class WebeeZigbee
{
private:
  ZigbeeRole_Typedef _Role;
  uint16_t _PanID;
  uint16_t _LocalMutiNumber;
  uint8_t _Channel;
  uint8_t _DataTramsmit[TRANSMIT_BUFFER_SIZE];

protected:
public:
  WebeeZigbee(void);
  WebeeZigbee(ZigbeeRole_Typedef Role, uint32_t PanID);
  bool setChannel(uint8_t Channel);
  bool setPanID(void);
  bool setPanID(uint32_t PanID);
  bool setRole(void);
  bool setRole(ZigbeeRole_Typedef Role);
  bool setLocalMultiNumber(uint16_t Addr);
  bool setNetworkKey(uint8_t *NetworkKey);
  bool sendDataBroadcast(uint8_t *pData, uint16_t Size);
  bool sendDataMulticast(uint16_t multicastNumber, uint8_t *pData, uint16_t Size);
  bool sendDataUnicast(uint16_t shortAddr, uint8_t *pData, uint16_t Size);
  void sendUart(uint8_t *pData, uint16_t Size, uint16_t timeOut);
};

#endif //ZIGBEE_WEBEE_HH_H
