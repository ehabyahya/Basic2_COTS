#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPES.h"


#include "DIO_interface.h"
#include "STPMotor_cfg.h"
#include "STPMotor_prv.h"
#include "STPMotor_interface.h"

#include "util/delay.h"





uint8 STPMotor_u8Rotate(const STPMotor_Config_t* copy_STPMotorObject,STPMotor_Direction_t copy_STPMotorDirection,uint16 copy_u16Angle)
{
	uint8 Local_u8ErrorState=OK;

	if(copy_STPMotorObject != NULL)
	{
		uint16 Local_u8Iterator;
		uint16 Local_u16Steps=(uint16)(((uint32)copy_u16Angle*2048UL)/360UL);
		if(copy_STPMotorDirection==STPMotor_ClockWise)
		{
			for(Local_u8Iterator=0;Local_u8Iterator<Local_u16Steps;Local_u8Iterator++)
			{
				if(Local_u8Iterator%4==0)
				{
					/* activate blue */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_LOW);
					/* deactivate pink, yellow, orange */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_HIGH);
				}
				else if(Local_u8Iterator%4==1)
				{
					/* activate pink */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_LOW);
					/* deactivate blue, yellow, orange */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_HIGH);
				}
				else if(Local_u8Iterator%4==2)
				{
					/* activate yellow */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_LOW);
					/* deactivate blue, pink, orange */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_HIGH);
				}
				else if(Local_u8Iterator%4==3)
				{
					/* activate orange */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_LOW);
					/* deactivate blue, pink, yellow */
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_HIGH);
					DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_HIGH);
				}
				_delay_ms(2);
			}
		}
		else if(copy_STPMotorDirection==STPMotor_CounterClockWise)
		{
			for(Local_u8Iterator=0;Local_u8Iterator<Local_u16Steps;Local_u8Iterator++)
			{
				for(Local_u8Iterator=0;Local_u8Iterator<Local_u16Steps;Local_u8Iterator++)
				{
					if(Local_u8Iterator%4==3)
					{
						/* activate blue */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_LOW);
						/* deactivate pink, yellow, orange */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_HIGH);
					}
					else if(Local_u8Iterator%4==2)
					{
						/* activate pink */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_LOW);
						/* deactivate blue, yellow, orange */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_HIGH);
					}
					else if(Local_u8Iterator%4==1)
					{
						/* activate yellow */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_LOW);
						/* deactivate blue, pink, orange */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_HIGH);
					}
					else if(Local_u8Iterator%4==0)
					{
						/* activate orange */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_OrangePin,DIO_PIN_LOW);
						/* deactivate blue, pink, yellow */
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_BluePin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_PinkPin,DIO_PIN_HIGH);
						DIO_u8SetPinValue(copy_STPMotorObject->STPMotor_Port,copy_STPMotorObject->STPMotor_YellowPin,DIO_PIN_HIGH);
					}
					_delay_ms(2);
				}
			}
		}
		else
			Local_u8ErrorState=NOK;
	}
	else
		Local_u8ErrorState=NULL_PTR;

	return Local_u8ErrorState;
}

