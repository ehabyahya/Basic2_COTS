#include "STD_TYPES.h"

#include "ERR_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_reg.h"
#include "DIO_interface.h"


uint8 DIO_u8SetPinDirection(DIO_Port_t Copy_Port,DIO_Pin_t Copy_PinNum,DIO_PinDir_t Copy_PinDir)
{
	uint8 Local_u8ErrorState=OK;
	if((Copy_PinNum >= DIO_PIN0)&&(Copy_PinNum <= DIO_PIN7 ))
	{
		if(Copy_PinDir==DIO_PIN_OUTPUT)
		{
			switch (Copy_Port) {
			case DIO_PORTA:SET_BIT(DDRA,Copy_PinNum); break;
			case DIO_PORTB:SET_BIT(DDRB,Copy_PinNum); break;
			case DIO_PORTC:SET_BIT(DDRC,Copy_PinNum); break;
			case DIO_PORTD:SET_BIT(DDRD,Copy_PinNum); break;
			default:Local_u8ErrorState=NOK;break;
			}
		}
		else if(Copy_PinDir==DIO_PIN_INPUT)
		{
			switch (Copy_Port) {
			case DIO_PORTA:CLR_BIT(DDRA,Copy_PinNum); break;
			case DIO_PORTB:CLR_BIT(DDRB,Copy_PinNum); break;
			case DIO_PORTC:CLR_BIT(DDRC,Copy_PinNum); break;
			case DIO_PORTD:CLR_BIT(DDRD,Copy_PinNum); break;
			default:Local_u8ErrorState=NOK;break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}



	return Local_u8ErrorState;
}
uint8 DIO_u8SetPortDirection(DIO_Port_t Copy_Port,uint8 Copy_u8PortDir)
{
	uint8 Local_u8ErrorState=OK;

	switch (Copy_Port) {
	case DIO_PORTA:DDRA=Copy_u8PortDir; break;
	case DIO_PORTB:DDRB=Copy_u8PortDir; break;
	case DIO_PORTC:DDRC=Copy_u8PortDir; break;
	case DIO_PORTD:DDRD=Copy_u8PortDir; break;
	default:Local_u8ErrorState=NOK;break;
	}


	return Local_u8ErrorState;
}
uint8 DIO_u8SetPinValue(DIO_Port_t Copy_Port,DIO_Pin_t Copy_PinNum,DIO_PinVal_t Copy_PinValue)
{
	uint8 Local_u8ErrorState=OK;
	if((Copy_PinNum >= DIO_PIN0)&&(Copy_PinNum <= DIO_PIN7 ))
	{
		if(Copy_PinValue==DIO_PIN_HIGH)
		{
			switch (Copy_Port) {
			case DIO_PORTA:SET_BIT(PORTA,Copy_PinNum); break;
			case DIO_PORTB:SET_BIT(PORTB,Copy_PinNum); break;
			case DIO_PORTC:SET_BIT(PORTC,Copy_PinNum); break;
			case DIO_PORTD:SET_BIT(PORTD,Copy_PinNum); break;
			default:Local_u8ErrorState=NOK;break;
			}
		}
		else if(Copy_PinValue==DIO_PIN_LOW)
		{
			switch (Copy_Port) {
			case DIO_PORTA:CLR_BIT(PORTA,Copy_PinNum); break;
			case DIO_PORTB:CLR_BIT(PORTB,Copy_PinNum); break;
			case DIO_PORTC:CLR_BIT(PORTC,Copy_PinNum); break;
			case DIO_PORTD:CLR_BIT(PORTD,Copy_PinNum); break;
			default:Local_u8ErrorState=NOK;break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}



	return Local_u8ErrorState;
}
uint8 DIO_u8SetPortValue(DIO_Port_t Copy_Port,uint8 Copy_u8PortValue)
{
	uint8 Local_u8ErrorState=OK;

	switch (Copy_Port) {
	case DIO_PORTA:PORTA=Copy_u8PortValue; break;
	case DIO_PORTB:PORTB=Copy_u8PortValue; break;
	case DIO_PORTC:PORTC=Copy_u8PortValue; break;
	case DIO_PORTD:PORTD=Copy_u8PortValue; break;
	default:Local_u8ErrorState=NOK;break;
	}

	return Local_u8ErrorState;
}
uint8 DIO_u8GetPinValue(DIO_Port_t Copy_Port,DIO_Pin_t Copy_PinNum,DIO_PinVal_t* Copy_PValue)
{
	uint8 Local_u8ErrorState=OK;

	if(Copy_PValue !=NULL)
	{
		if((Copy_PinNum >= DIO_PIN0)&&(Copy_PinNum <= DIO_PIN7 ))
		{
			switch (Copy_Port) {
			case DIO_PORTA:*Copy_PValue=GET_BIT(PINA,Copy_PinNum); break;
			case DIO_PORTB:*Copy_PValue=GET_BIT(PINB,Copy_PinNum); break;
			case DIO_PORTC:*Copy_PValue=GET_BIT(PINC,Copy_PinNum); break;
			case DIO_PORTD:*Copy_PValue=GET_BIT(PIND,Copy_PinNum); break;
			default:Local_u8ErrorState=NOK;break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR;
	}

	return Local_u8ErrorState;
}



uint8 DIO_u8TogglePinValue(DIO_Port_t copy_Port,DIO_Pin_t copy_PinNUM)
{
	uint8 Local_u8ErrorState=OK;


	if((copy_PinNUM >= DIO_PIN0)&&(copy_PinNUM <= DIO_PIN7 ))
	{
		switch (copy_Port) {
		case DIO_PORTA:TOG_BIT(PORTA,copy_PinNUM); break;
		case DIO_PORTB:TOG_BIT(PORTB,copy_PinNUM); break;
		case DIO_PORTC:TOG_BIT(PORTC,copy_PinNUM); break;
		case DIO_PORTD:TOG_BIT(PORTD,copy_PinNUM); break;
		default:Local_u8ErrorState=NOK;break;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}





	return Local_u8ErrorState;
}





