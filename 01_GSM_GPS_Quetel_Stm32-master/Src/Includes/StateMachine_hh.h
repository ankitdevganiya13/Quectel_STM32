#ifndef STATE_MACHINE_HH_H
#define	STATE_MACHINE_HH_H
#include "stdint.h"

extern uint8_t App_StateMachine_xdu8;

typedef enum 
{
	STATE_INIT,
	STATE_READY,
	STATE_ERROR,
} StateMachine_Typedef;




void StateMachine(void);

#endif	//STATE_MACHINE_HH_H
