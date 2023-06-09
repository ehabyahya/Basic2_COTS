#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


typedef enum
{
	DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}DIO_Port_t;


typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}DIO_Pin_t;




typedef enum
{
	DIO_PIN_INPUT,
	DIO_PIN_OUTPUT
}DIO_PinDir_t;



typedef enum
{
	DIO_PIN_LOW,
	DIO_PIN_HIGH
}DIO_PinVal_t;



uint8 DIO_u8SetPinDirection(DIO_Port_t Copy_Port,DIO_Pin_t Copy_PinNum,DIO_PinDir_t Copy_PinDir);
uint8 DIO_u8SetPortDirection(DIO_Port_t Copy_Port,uint8 Copy_u8PortDir);

uint8 DIO_u8SetPinValue(DIO_Port_t Copy_Port,DIO_Pin_t Copy_PinNum,DIO_PinVal_t Copy_PinValue);
uint8 DIO_u8SetPortValue(DIO_Port_t Copy_Port,uint8 Copy_u8PortValue);

uint8 DIO_u8GetPinValue(DIO_Port_t Copy_Port,DIO_Pin_t Copy_PinNum,DIO_PinVal_t* Copy_PValue);

uint8 DIO_u8TogglePinValue(DIO_Port_t copy_Port,DIO_Pin_t copy_PinNUM);


#endif
