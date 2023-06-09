#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPES.h"


#include "DIO_interface.h"
#include "SSD_interface.h"
#include "SSD_cfg.h"
#include "SSD_prv.h"






uint8 SSD_u8SetNumber(const SSD_Config_t* copy_SSDObject,uint8 copy_u8Number)
{
	uint8 Local_u8ErrorState=OK;
	uint8 Local_PinIterator,Local_PinIterator2=0;

	if(copy_SSDObject != NULL)
	{
		if(copy_u8Number<=9)
		{
			static uint8 Local_u8ArrNumbers[10]={0b00111111,0b00000110,
					0b01011011,0b01001111,0b01100110,0b01101101,
					0b01111101,0b00000111,0b01111111,0b01101111};

			/* set value of LED pins*/
			if((copy_SSDObject->SSD_Type==SSD_CommonCasthod)||(copy_SSDObject->SSD_Type==SSD_EtaKit))
			{
				for(Local_PinIterator=copy_SSDObject->SSD_StartPin;Local_PinIterator<7;Local_PinIterator++)
				{
					DIO_u8SetPinValue(copy_SSDObject->SSD_Port,Local_PinIterator,GET_BIT(Local_u8ArrNumbers[copy_u8Number],Local_PinIterator2));
					Local_PinIterator2++;
				}
			}
			else if(copy_SSDObject->SSD_Type==SSD_CommonAnode)
			{
				for(Local_PinIterator=copy_SSDObject->SSD_StartPin;Local_PinIterator<7;Local_PinIterator++)
				{
					DIO_u8SetPinValue(copy_SSDObject->SSD_Port,Local_PinIterator,GET_BIT(~Local_u8ArrNumbers[copy_u8Number],Local_PinIterator2));
					Local_PinIterator2++;
				}
			}

			else
				Local_u8ErrorState=NOK;
		}
		else
			Local_u8ErrorState=NOK;
	}
	else
		Local_u8ErrorState=NULL_PTR;


	return Local_u8ErrorState;
}
uint8 SSD_u8Enable(const SSD_Config_t* copy_SSDObject)
{
	uint8 Local_u8ErrorState=OK;
	if(copy_SSDObject != NULL)
	{
		if(copy_SSDObject->SSD_StartPin==DIO_PIN0||copy_SSDObject->SSD_StartPin==DIO_PIN1)
		{
			/* set value for common pin*/
			if((copy_SSDObject->SSD_Type==SSD_CommonAnode)&&(copy_SSDObject->SSD_Type==SSD_EtaKit))
			{
				DIO_u8SetPinValue(copy_SSDObject->SSD_EnablePort,copy_SSDObject->SSD_EnablePin,DIO_PIN_HIGH);
			}
			else if(copy_SSDObject->SSD_Type==SSD_CommonCasthod)
			{
				DIO_u8SetPinValue(copy_SSDObject->SSD_EnablePort,copy_SSDObject->SSD_EnablePin,DIO_PIN_LOW);
			}
			else
				Local_u8ErrorState=NOK;
		}
		else
			Local_u8ErrorState=NOK;
	}
	else
		Local_u8ErrorState=NULL_PTR;


	return Local_u8ErrorState;
}
uint8 SSD_u8Disable(const SSD_Config_t* copy_SSDObject)
{
	uint8 Local_u8ErrorState=OK;
	if(copy_SSDObject != NULL)
	{
		/* set inverse value for common pin*/
		if((copy_SSDObject->SSD_Type==SSD_CommonAnode)&&(copy_SSDObject->SSD_Type==SSD_EtaKit))
		{
			DIO_u8SetPinValue(copy_SSDObject->SSD_EnablePort,copy_SSDObject->SSD_EnablePin,DIO_PIN_LOW);
		}
		else if(copy_SSDObject->SSD_Type==SSD_CommonCasthod)
		{
			DIO_u8SetPinValue(copy_SSDObject->SSD_EnablePort,copy_SSDObject->SSD_EnablePin,DIO_PIN_HIGH);
		}
		else
			Local_u8ErrorState=NOK;
	}
	else
		Local_u8ErrorState=NULL_PTR;


	return Local_u8ErrorState;
}




