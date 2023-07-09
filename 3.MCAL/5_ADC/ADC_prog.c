#include  "STD_TYPES.h"
#include  "BIT_MATH.h"
#include  "ERR_TYPES.h"

#include "ADC_interface.h"
#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"



/* flag to protect from shared resources "re-entrancy" */
static uint8 ADC_u8BusyFalg= IDLE;


/* global variables for Asynchronous ADC */
static uint16* ADC_pu16DigtalResult = NULL;
static void (*ADC_pfvNotificationFunc)(void)=NULL;

/* global variables for Chain Asynchronous ADC */
static uint8 ADC_u8ChainIndex = FIRST_INDEX;
static ADC_Chain_t* ADC_psChainConversions = NULL;

/* flag for ISR to know type of conversions */
static uint8 ADC_u8Conversiontype;


void   ADC_voidInit(void)
{
	/* select reverence selection  */
	ADMUX &= REFERENCE_MASK;
	ADMUX |= (ADC_u8REFRENCE << 6) ;


	/* select ADC Bits Type  */
#if	ADC_u8RESOLUTION == EIGHT_BITS
	/* activate left adjust result for 8-bit resolution*/
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8RESOLUTION == TEN_BITS
	/* deactivate left adjust result for 10-bit resolution*/
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error  wrong ADC_u8RESOLUTION configuration value
#endif




	/* select ADC prescaler  */
	ADCSRA &= PRESCALER_MASK;
	ADCSRA |= ADC_u8PRESCALER ;



}
void   ADC_voidEnable(void)
{
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}
void   ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA,ADCSRA_ADEN);
}
uint8 ADC_u16StartConversionSynch(ADC_Channel_t  copy_eChannel,uint16* copy_pu16DigitalResult)
{
	uint8 Local_u8ErrorState = OK;


	if(copy_pu16DigitalResult != NULL)
	{
		if(ADC_u8BusyFalg==IDLE)
		{
			uint32  Local_u32Counter =0u;

			/* now, ADC is Busy */
			ADC_u8BusyFalg=BUSY;


			/* set channel and gain selection */
			ADMUX 	&= 	CHANNEL_MASK;
			ADMUX 	|=  copy_eChannel ;

			/* start conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/* wait"block" "bolling" until conversion is completed or the timeout has not passed yet */
			while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0)&&(Local_u32Counter < ADC_u32TIMEOUT_COUNT))
			{
				Local_u32Counter++;
			}
			if(Local_u32Counter == ADC_u32TIMEOUT_COUNT)
			{
				/* loop  is broken because time out has passed */
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else  /* loop  is broken because flag is raised */
			{
				/* clear conversion complete flag */
				SET_BIT(ADCSRA,ADCSRA_ADIF);

#if  ADC_u8RESOLUTION==EIGHT_BITS
				*copy_pu16DigitalResult= (uint16)ADCH;
#elif	ADC_u8RESOLUTION==TEN_BITS
				*copy_pu16DigitalResult= ADC;
#endif

			}


			/* task is done, now, ADC is IDLE  */
			ADC_u8BusyFalg = IDLE;
		}
		else {
			/* do nothing */
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 ADC_u16StartConversionASynch(ADC_Channel_t  copy_eChannel,uint16* copy_pu16DigitalResult, void (*copy_pfvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;


	if((copy_pu16DigitalResult != NULL) && (copy_pfvNotificationFunc != NULL))
	{
		if(ADC_u8BusyFalg==IDLE)
		{
			/* now, ADC is Busy */
			ADC_u8BusyFalg = BUSY;

			/* conversion type is single */
			ADC_u8Conversiontype = SINGLE_CONVERSION;

			/* convert the digital result and the notification function local into global */
			ADC_pu16DigtalResult=copy_pu16DigitalResult;
			ADC_pfvNotificationFunc=copy_pfvNotificationFunc;

			/* set channel and gain selection */
			ADMUX 	&= 	CHANNEL_MASK;
			ADMUX 	|=  copy_eChannel ;

			/* start conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/* enable ADC conversion complete interrupt  */
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/* do nothing */
			Local_u8ErrorState=BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR;
	}
	return Local_u8ErrorState;
}

uint8 ADC_u16StartChainConversionASynch(const ADC_Chain_t* copy_psChainObject)
{
	uint8 Local_u8ErrorState = OK;
	if((copy_psChainObject != NULL)&&(copy_psChainObject->ADC_peChannels != NULL)&&(copy_psChainObject->ADC_pu16Results != NULL)&&(copy_psChainObject->ADC_pfvNotificationFunction!=NULL))
	{
		if(ADC_u8BusyFalg==IDLE)
		{
			/* now, ADC is Busy */
			ADC_u8BusyFalg = BUSY;

			/* conversion type is chain */
			ADC_u8Conversiontype = CHAIN_CONVERSION;



			/* reset index every call */
			ADC_u8ChainIndex=FIRST_INDEX;
			/* save local struct to global struct for ISR*/
			ADC_psChainConversions = (ADC_Chain_t*)copy_psChainObject;


			/* set channel and gain selection */
			ADMUX 	&= 	CHANNEL_MASK;
			ADMUX 	|=  ADC_psChainConversions->ADC_peChannels[ADC_u8ChainIndex] ;


			/* start conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/* enable ADC conversion complete interrupt  */
			SET_BIT(ADCSRA,ADCSRA_ADIE);


		}
		else
		{
			/* do nothing */
			Local_u8ErrorState=BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR;
	}

	return Local_u8ErrorState;
}

uint16 ADC_u16GetAnalogVolt(uint16 copy_u16ADC_Reading)
{
#if  ADC_u8RESOLUTION==EIGHT_BITS
	return (uint16)(((uint32)copy_u16ADC_Reading*5000UL)/256UL);
#elif	ADC_u8RESOLUTION==TEN_BITS
	return (uint16)(((uint32)copy_u16ADC_Reading*5000UL)/1024UL);
#endif
}






/* ADC conversion complete ISR */
void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{

	if(ADC_u8Conversiontype==SINGLE_CONVERSION)
	{


#if  ADC_u8RESOLUTION==EIGHT_BITS
		*ADC_pu16DigtalResult = (uint16)ADCH;
#elif	ADC_u8RESOLUTION==TEN_BITS
		*ADC_pu16DigtalResult = ADC;
#endif


		/* ADC interrupt disable */
		CLR_BIT(ADCSRA,ADCSRA_ADIE);


		/* task is done, now, ADC is IDLE  */
		ADC_u8BusyFalg = IDLE;


		/* invoke the callback notification function */
		if(ADC_pfvNotificationFunc!=NULL)
		{
			ADC_pfvNotificationFunc();
		}
		else {
			/* Do nothing */
		}



	}
	else if(ADC_u8Conversiontype==CHAIN_CONVERSION)
	{

#if  ADC_u8RESOLUTION==EIGHT_BITS
		ADC_psChainConversions->ADC_pu16Results[ADC_u8ChainIndex] = (uint16)ADCH;
#elif	ADC_u8RESOLUTION==TEN_BITS
		ADC_psChainConversions->ADC_pu16Results[ADC_u8ChainIndex] = ADC;
#endif

		/* increment index to go to next conversion */
		ADC_u8ChainIndex++;


		/* if all conversions were completed */
		if(ADC_u8ChainIndex == ADC_psChainConversions->ADC_u8NumConversions)
		{
			/* task is done, now, ADC is IDLE  */
			ADC_u8BusyFalg = IDLE;

			/* ADC interrupt disable */
			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			/* reset the index of conversions */
			ADC_u8ChainIndex=FIRST_INDEX;


			/* invoke the callback notification function */
			if(ADC_psChainConversions->ADC_pfvNotificationFunction!=NULL)
			{
				ADC_psChainConversions->ADC_pfvNotificationFunction();
			}
			else {
				/* Do nothing */
			}
		}
		else /* start the next conversion */
		{
			/* set channel and gain selection */
			ADMUX 	&= 	CHANNEL_MASK;
			ADMUX 	|=  ADC_psChainConversions->ADC_peChannels[ADC_u8ChainIndex] ;

			/* start conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);
		}

	}
	else {
		/* Do nothing */
	}



}


