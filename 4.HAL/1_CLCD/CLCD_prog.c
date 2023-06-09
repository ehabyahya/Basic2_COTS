#include "STD_TYPES.h"
#include<util/delay.h>
#include"BIT_MATH.h"
#include"ERR_TYPES.h"

#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"



#if CLCD_u8CONNECTION_MODE == FOUR_BIT
static void voidSetHalfDataPort(uint8 copy_u8FourBitData)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN,GET_BIT(copy_u8FourBitData,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN,GET_BIT(copy_u8FourBitData,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN,GET_BIT(copy_u8FourBitData,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN,GET_BIT(copy_u8FourBitData,3));
}
#endif
static void voidSendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_LOW);
}




void CLCD_voidSendCommand(uint8 copy_u8Command)
{
	/*1- set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_LOW);

	/*2- set RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif


#if CLCD_u8CONNECTION_MODE == FOUR_BIT

	/*3- send the command higher four bits*/
	voidSetHalfDataPort(copy_u8Command>>4u);

	/*4- send enable pulse*/
	voidSendEnablePulse();

	/*5- send the command lower four bits*/
	voidSetHalfDataPort(copy_u8Command);
	/*6- send enable pulse*/
	voidSendEnablePulse();



#elif CLCD_u8CONNECTION_MODE == EIGHT_BIT

	/*3- send the command*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Command);

	/*4- send enable pulse*/
	voidSendEnablePulse();
#endif




}
void CLCD_voidSendData(uint8 copy_u8Data)
{
	/*1- set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_HIGH);

	/*2- set RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif


#if CLCD_u8CONNECTION_MODE == FOUR_BIT

	/*3- send the command higher four bits*/
	voidSetHalfDataPort(copy_u8Data>>4u);

	/*4- send enable pulse*/
	voidSendEnablePulse();

	/*5- send the command lower four bits*/
	voidSetHalfDataPort(copy_u8Data);
	/*6- send enable pulse*/
	voidSendEnablePulse();



#elif CLCD_u8CONNECTION_MODE == EIGHT_BIT

	/*3- send the command*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Data);

	/*4- send enable pulse*/
	voidSendEnablePulse();
#endif



}
void CLCD_voidInit(void)
{
	/*1- wait for more than 30ms after power on*/
	_delay_ms(40);

	/*2- function set command: 2 lines, font size 5X7 */
#if CLCD_u8CONNECTION_MODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000);

#elif CLCD_u8CONNECTION_MODE == FOUR_BIT
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif
	/*3- display on/off control: display on, cursor off, blink off */
	CLCD_voidSendCommand(0b00001100);

	/*4- display clear */
	CLCD_voidSendCommand(1);

}
void CLCD_voidGoToXY(uint8 copy_u8Xpos,uint8 copy_u8Ypos)
{
	uint8 Local_u8DDRamAdd=(copy_u8Ypos*0x40u)+copy_u8Xpos;

	/*set bit 7 for setting DDRAM address command*/
	SET_BIT(Local_u8DDRamAdd,7u);

	CLCD_voidSendCommand(Local_u8DDRamAdd);

}
uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_u8PatternNumber,uint8 copy_pu8PatternArr[],uint8 copy_u8XPos,uint8 copy_u8YPos)
{
	uint8 Local_u8ErrorStatus=OK;

	if(copy_pu8PatternArr!=NULL)
	{
		uint8 Local_u8Iterator;
		uint8 Local_u8CGRamAdd=copy_u8PatternNumber*8u;

		/*set bit 6 and clear bit 7 for setting CGRam address command*/
		SET_BIT(Local_u8CGRamAdd,6u);

		/*set  CGRam address */
		CLCD_voidSendCommand(Local_u8CGRamAdd);

		/* write the pattern inside CGRam*/
		for(Local_u8Iterator=0u;Local_u8Iterator<8u;Local_u8Iterator++)
		{
			CLCD_voidSendData(copy_pu8PatternArr[Local_u8Iterator]);
		}

		/* set DDRam address*/
		CLCD_voidGoToXY(copy_u8XPos,copy_u8YPos);

		/*write the corresponding pattern number to display from CGRam*/
		CLCD_voidSendData(copy_u8PatternNumber);


	}
	else
	{
		Local_u8ErrorStatus=NULL_PTR;
	}




	return Local_u8ErrorStatus;
}

void CLCD_voidWriteNumber(sint32 copy_s32Number)
{
	char Local_chNumbers[10];
	uint8 Local_u8RightDigit,Local_u8Counter1=0;
	sint8 Local_u8Counter2;

	if(copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if(copy_s32Number < 0)
	{
		/* Number is negative , print -ve sign*/
		CLCD_voidSendData('-');
		copy_s32Number *=-1;
	}

	while(copy_s32Number!=0)
	{
		Local_u8RightDigit=copy_s32Number%10; //get the right most digit
		copy_s32Number/=10;                  // get rid of the right most digit

		Local_chNumbers[Local_u8Counter1] = Local_u8RightDigit+'0';
		Local_u8Counter1++;
	}

	for( Local_u8Counter2 = (sint8)Local_u8Counter1 - 1 ; Local_u8Counter2 >= 0 ; Local_u8Counter2-- )
	{
		CLCD_voidSendData(Local_chNumbers[(uint8)Local_u8Counter2]);
	}

}
void CLCD_voidWriteStringData(uint8* copy_u8PString)
{
	uint8 i;
	while(copy_u8PString[i]!='\0')
	{
		CLCD_voidSendData(copy_u8PString[i]);
		i++;
	}
}

