#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "SSD_interface.h"


void main(void)
{
	uint32 i;
	SSD_Config_t SSD_ComAnode={SSD_CommonAnode,
			DIO_PORTA,DIO_PIN1,DIO_PORTB,DIO_PIN0};

	SSD_Config_t SSD_ComCathod={SSD_CommonCasthod,
			DIO_PORTC,DIO_PIN0,DIO_PORTD,DIO_PIN7};

	SSD_u8Enable(&SSD_ComAnode);
	SSD_u8SetNumber(&SSD_ComAnode,7);
	_delay_ms(1000);
	SSD_u8Disable(&SSD_ComAnode);


	SSD_u8Enable(&SSD_ComCathod);
	SSD_u8SetNumber(&SSD_ComCathod,4);
	_delay_ms(2000);
	SSD_u8Disable(&SSD_ComCathod);



	while(1)
	{

		/*for(i=0;i<100;i++)
			{
				SSD_u8Enable(&SSD_ComAnode);
				SSD_u8SetNumber(&SSD_ComAnode,i/10);
				_delay_ms(200);

				SSD_u8Enable(&SSD_ComCathod);
				SSD_u8SetNumber(&SSD_ComCathod,i%10);
				_delay_ms(200);
			}
			_delay_ms(10000);*/
	}
}



