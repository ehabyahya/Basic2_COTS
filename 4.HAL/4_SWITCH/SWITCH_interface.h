#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H


typedef enum
{
	SWITCH_PRESSED,
	SWITCH_RELEASED

}SWITCH_State_t;

typedef enum
{
	SWITCH_PULL_UP,
	SWITCH_PULL_DOWN

}SWITCH_Pull_t;


typedef struct
{
	DIO_Port_t 		SWITCH_PORT;
	DIO_Pin_t  		SWITCH_PIN;
	SWITCH_Pull_t 	SWITCH_Pull;
}SWITCH_Config_t;


uint8 SWITCH_u8GetState(const SWITCH_Config_t* copy_SWITCHObject,SWITCH_State_t* copy_SWITCHState);






#endif
