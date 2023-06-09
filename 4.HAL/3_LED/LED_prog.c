#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPES.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_cfg.h"
#include "LED_prv.h"




uint8 LED_u8ON(const LED_Config_t* copy_LEDObject)
{
	uint8 Local_u8ErrorStatus=OK;
	if(copy_LEDObject != NULL)
	{

		/* set pin value */
		if(copy_LEDObject->LED_ACTIVITY==LED_ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(copy_LEDObject->LED_PORT,copy_LEDObject->LED_PIN,DIO_PIN_HIGH);
		}
		else if(copy_LEDObject->LED_ACTIVITY==LED_ACTIVE_LOW)
		{
			DIO_u8SetPinValue(copy_LEDObject->LED_PORT,copy_LEDObject->LED_PIN,DIO_PIN_LOW);
		}
		else
			Local_u8ErrorStatus=NOK;
	}
	else
		Local_u8ErrorStatus=NULL_PTR;


	return Local_u8ErrorStatus;
}
uint8 LED_u8OFF(const LED_Config_t* copy_LEDObject)
{
	uint8 Local_u8ErrorStatus=OK;
	if(copy_LEDObject != NULL)
	{
		/* clear pin value */
		if(copy_LEDObject->LED_ACTIVITY==LED_ACTIVE_HIGH)
		{
			DIO_u8SetPinValue(copy_LEDObject->LED_PORT,copy_LEDObject->LED_PIN,DIO_PIN_LOW);
		}
		else if(copy_LEDObject->LED_ACTIVITY==LED_ACTIVE_LOW)
		{
			DIO_u8SetPinValue(copy_LEDObject->LED_PORT,copy_LEDObject->LED_PIN,DIO_PIN_HIGH);
		}
		else
			Local_u8ErrorStatus=NOK;
	}
	else
		Local_u8ErrorStatus=NULL_PTR;

	return Local_u8ErrorStatus;
}
uint8 LED_u8TOGGLE(const LED_Config_t* copy_LEDObject)
{
	uint8 Local_u8ErrorStatus=OK;
	if(copy_LEDObject != NULL)
	{
		/* toggle pin value */
		DIO_u8TogglePinValue(copy_LEDObject->LED_PORT,copy_LEDObject->LED_PIN);
	}
	else
		Local_u8ErrorStatus=NULL_PTR;

	return Local_u8ErrorStatus;
}



