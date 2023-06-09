#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPES.h"

#include "DIO_interface.h"
#include "SWITCH_cfg.h"
#include "SWITCH_interface.h"
#include "SWITCH_prv.h"



uint8 SWITCH_u8GetState(const SWITCH_Config_t* copy_SWITCHObject,SWITCH_State_t* copy_SWITCHState)
{
	uint8 Local_u8ErrorStatus=OK;
	uint8 Local_u8SwitchValue;

	if((copy_SWITCHObject != NULL) &&(copy_SWITCHState != NULL) )
	{
		/* Get pin value */
		DIO_u8GetPinValue(copy_SWITCHObject->SWITCH_PORT,copy_SWITCHObject->SWITCH_PIN,&Local_u8SwitchValue);

		if(Local_u8SwitchValue==DIO_PIN_LOW)
		{
			if(copy_SWITCHObject->SWITCH_Pull==SWITCH_PULL_UP)
			{
				*copy_SWITCHState=SWITCH_PRESSED;
			}
			else if(copy_SWITCHObject->SWITCH_Pull==SWITCH_PULL_DOWN)
			{
				*copy_SWITCHState=SWITCH_RELEASED;
			}
			else
				Local_u8ErrorStatus=NOK;
		}
		else if(Local_u8SwitchValue==DIO_PIN_HIGH)
		{
			if(copy_SWITCHObject->SWITCH_Pull==SWITCH_PULL_UP)
			{
				*copy_SWITCHState=SWITCH_RELEASED;
			}
			else if(copy_SWITCHObject->SWITCH_Pull==SWITCH_PULL_DOWN)
			{
				*copy_SWITCHState=SWITCH_PRESSED;
			}
			else
				Local_u8ErrorStatus=NOK;
		}
		else
			Local_u8ErrorStatus=NOK;
	}
	else
		Local_u8ErrorStatus=NULL_PTR;


	return Local_u8ErrorStatus;
}


