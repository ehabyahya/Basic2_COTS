#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"ERR_TYPES.h"


#include "PORT_interface.h"
#include "DIO_interface.h"
#include "KPD_interface.h"
#include "KPD_cfg.h"
#include "KPD_prv.h"





uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8RowCounter,Local_u8ColCounter,Local_u8GetState,Local_u8GetKey=KPD_u8NO_PRESSED;

	static uint8 Local_u8ROWARR[ROW_NUM]={KPD_u8R0_PIN,KPD_u8R1_PIN,KPD_u8R2_PIN,KPD_u8R3_PIN};
	static uint8 Local_u8COLARR[COL_NUM]={KPD_u8C0_PIN,KPD_u8C1_PIN,KPD_u8C2_PIN,KPD_u8C3_PIN};
	static uint8 Local_u8KPDARR[ROW_NUM][COL_NUM]=KPD_u8BUTTON_ARR;


	for(Local_u8ColCounter=0u;Local_u8ColCounter<COL_NUM;Local_u8ColCounter++)
	{
		/*Activate the current Column as LOW*/
		DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8COLARR[Local_u8ColCounter],DIO_PIN_LOW);

		/* loop on row button and get any button was pressed */
		for(Local_u8RowCounter=0u;Local_u8RowCounter<ROW_NUM;Local_u8RowCounter++)
		{
			DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8ROWARR[Local_u8RowCounter],&Local_u8GetState);
			if(Local_u8GetState==DIO_PIN_LOW)
			{
				Local_u8GetKey=Local_u8KPDARR[Local_u8RowCounter][Local_u8ColCounter];

				/* wait until key is released (polling with blocking on pin reading)*/
				while(Local_u8GetState==DIO_PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_u8ROW_PORT,Local_u8ROWARR[Local_u8RowCounter],&Local_u8GetState);
				}
				return Local_u8GetKey;
			}
		}

		/*Deactivate the current Column as HIGH*/
		DIO_u8SetPinValue(KPD_u8COL_PORT,Local_u8COLARR[Local_u8ColCounter],DIO_PIN_HIGH);
	}




	return Local_u8GetKey;

}



