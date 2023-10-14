#include "ZigbeeWebee_hh.h"
#include "stdint.h"

void WebeeZigbee::sendUart(uint8_t *pData, uint16_t Size, uint16_t timeOut)
{
  HAL_UART_Transmit(&huart3, pData, Size, timeOut);
}
WebeeZigbee::WebeeZigbee(void)
{
}
WebeeZigbee::WebeeZigbee(ZigbeeRole_Typedef Role, uint32_t PanID)
{
  this->_Role = Role;
  this->_PanID = PanID;
  this->_DataTramsmit[0] = 0x5A;
  this->_DataTramsmit[1] = 0xAA;
}
bool WebeeZigbee::setChannel(uint8_t Channel)
{
  this->_Channel = Channel;
  this->_DataTramsmit[2] = 0x03;
  this->_DataTramsmit[3] = 0x01;
  this->_DataTramsmit[4] = Channel;
  sendUart(this->_DataTramsmit, 5, 1000);
  return true;
}
bool WebeeZigbee::setPanID(void)
{
  return setPanID(_PanID);
}
bool WebeeZigbee::setPanID(uint32_t PanID)
{
  this->_PanID = PanID;
  this->_DataTramsmit[2] = 0x02;
  this->_DataTramsmit[3] = 0x02;
  this->_DataTramsmit[4] = PanID >> 8;
  this->_DataTramsmit[5] = PanID;
  sendUart(this->_DataTramsmit, 6, 1000);
  return true;
}
bool WebeeZigbee::setRole(void)
{
  return setRole(_Role);
}
bool WebeeZigbee::setRole(ZigbeeRole_Typedef Role)
{
  this->_Role = Role;
  this->_DataTramsmit[2] = 0x01;
  this->_DataTramsmit[3] = 0x01;
  this->_DataTramsmit[4] = Role;
  sendUart(this->_DataTramsmit, 5, 1000);
  return true;
}
bool WebeeZigbee::setLocalMultiNumber(uint16_t Addr)
{
  this->_LocalMutiNumber = Addr;
  this->_DataTramsmit[2] = 0x06;
  this->_DataTramsmit[3] = 0x02;
  this->_DataTramsmit[4] = Addr >> 8;
  this->_DataTramsmit[5] = Addr;
  sendUart(this->_DataTramsmit, 6, 1000);
  return true;
}
bool WebeeZigbee::setNetworkKey(uint8_t *NetworkKey)
{
  this->_DataTramsmit[2] = 0x0A;
  this->_DataTramsmit[3] = 0x10;
  for (uint8_t i = 0; i < 16; i++)
  {
    this->_DataTramsmit[i + 4] = *(NetworkKey + i);
  }
  sendUart(this->_DataTramsmit, 20, 1000);
  return true;
}
bool WebeeZigbee::sendDataBroadcast(uint8_t *pData, uint16_t Size)
{
  this->_DataTramsmit[2] = 0xA1;
  this->_DataTramsmit[3] = Size;
  for (uint8_t i = 0; i < Size; i++)
  {
    this->_DataTramsmit[i + 4] = *(pData + i);
  }
  sendUart(this->_DataTramsmit, Size + 4, 1000);
  return true;
}

bool WebeeZigbee::sendDataMulticast(uint16_t muticastNumber, uint8_t *pData, uint16_t Size)
{
  this->_DataTramsmit[2] = 0xA2;
  this->_DataTramsmit[3] = Size;
  this->_DataTramsmit[4] = muticastNumber >> 8;
  this->_DataTramsmit[5] = muticastNumber;
  for (int i = 0; i < Size; i++)
  {
    this->_DataTramsmit[i + 6] = *(pData + i);
  }
  sendUart(this->_DataTramsmit, Size + 6, 1000);
  return true;
}
bool WebeeZigbee::sendDataUnicast(uint16_t shortAddr, uint8_t *pData, uint16_t Size)
{
  this->_DataTramsmit[2] = 0xA3;
  this->_DataTramsmit[3] = Size;
  this->_DataTramsmit[4] = shortAddr >> 8;
  this->_DataTramsmit[5] = shortAddr;
  for (int i = 0; i < Size; i++)
  {
    this->_DataTramsmit[i + 6] = *(pData + i);
  }
  sendUart(this->_DataTramsmit, Size + 6, 1000);
  return true;
}
