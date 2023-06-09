#include 	"STD_TYPES.h"
#include 	"ERR_TYPES.h"
#include 	"BIT_MATH.h"

#include 	"DIO_interface.h"
#include	"DCMotor_interface.h"
#include    "DCMotor_prv.h"
#include    "DCMotor_cfg.h"





uint8 DCMotor_u8CW_Direction(const DCMotor_Config_t* copy_DCMotorObject)
{
	uint8 Local_u8ErrorState=OK;
	if(copy_DCMotorObject != NULL)
	{
		DIO_u8SetPinValue(copy_DCMotorObject->DCMotor_Port,copy_DCMotorObject->DCMotor_Pin2,DIO_PIN_LOW);
		DIO_u8SetPinValue(copy_DCMotorObject->DCMotor_Port,copy_DCMotorObject->DCMotor_Pin1,DIO_PIN_HIGH);
	}
	else
		Local_u8ErrorState=NULL_PTR;

	return Local_u8ErrorState;
}
uint8 DCMotor_u8CCW_Direction(const DCMotor_Config_t* copy_DCMotorObject)
{
	uint8 Local_u8ErrorState=OK;
	if(copy_DCMotorObject != NULL)
	{
		DIO_u8SetPinValue(copy_DCMotorObject->DCMotor_Port,copy_DCMotorObject->DCMotor_Pin1,DIO_PIN_LOW);
		DIO_u8SetPinValue(copy_DCMotorObject->DCMotor_Port,copy_DCMotorObject->DCMotor_Pin2,DIO_PIN_HIGH);
	}
	else
		Local_u8ErrorState=NULL_PTR;

	return Local_u8ErrorState;
}
uint8 DCMotor_u8Stop(const DCMotor_Config_t* copy_DCMotorObject)
{
	uint8 Local_u8ErrorState=OK;
	if(copy_DCMotorObject != NULL)
	{
		DIO_u8SetPinValue(copy_DCMotorObject->DCMotor_Port,copy_DCMotorObject->DCMotor_Pin1,DIO_PIN_LOW);
		DIO_u8SetPinValue(copy_DCMotorObject->DCMotor_Port,copy_DCMotorObject->DCMotor_Pin2,DIO_PIN_LOW);
	}
	else
		Local_u8ErrorState=NULL_PTR;

	return Local_u8ErrorState;
}













