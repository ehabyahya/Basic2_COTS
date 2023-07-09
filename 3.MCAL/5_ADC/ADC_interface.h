#ifndef			ADC_INTERFACE_H
#define			ADC_INTERFACE_H

typedef enum
{
	ADC0_SINGLE_ENDED=0,
	ADC1_SINGLE_ENDED,
	ADC2_SINGLE_ENDED,
	ADC3_SINGLE_ENDED,
	ADC4_SINGLE_ENDED,
	ADC5_SINGLE_ENDED,
	ADC6_SINGLE_ENDED,
	ADC7_SINGLE_ENDED,
	ADC0_POS_ADC0_NEG_10X_GAIN,
	ADC1_POS_ADC0_NEG_10X_GAIN,
	ADC0_POS_ADC0_NEG_200X_GAIN,
	ADC1_POS_ADC0_NEG_200X_GAIN,
	ADC2_POS_ADC2_NEG_10X_GAIN,
	ADC3_POS_ADC2_NEG_10X_GAIN,
	ADC2_POS_ADC2_NEG_200X_GAIN,
	ADC3_POS_ADC2_NEG_200X_GAIN,
	ADC0_POS_ADC1_NEG_1X_GAIN,
	ADC1_POS_ADC1_NEG_1X_GAIN,
	ADC2_POS_ADC1_NEG_1X_GAIN,
	ADC3_POS_ADC1_NEG_1X_GAIN,
	ADC4_POS_ADC1_NEG_1X_GAIN,
	ADC5_POS_ADC1_NEG_1X_GAIN,
	ADC6_POS_ADC1_NEG_1X_GAIN,
	ADC7_POS_ADC1_NEG_1X_GAIN,
	ADC0_POS_ADC2_NEG_1X_GAIN,
	ADC1_POS_ADC2_NEG_1X_GAIN,
	ADC2_POS_ADC2_NEG_1X_GAIN,
	ADC3_POS_ADC2_NEG_1X_GAIN,
	ADC4_POS_ADC2_NEG_1X_GAIN,
	ADC5_POS_ADC2_NEG_1X_GAIN,
	V1_22__SINGLE_ENDED,
	V0__SINGLE_ENDED
}ADC_Channel_t;

typedef struct
{
	uint8   ADC_u8NumConversions;
	ADC_Channel_t*  ADC_peChannels;
	uint16*  ADC_pu16Results;
	void (*ADC_pfvNotificationFunction)(void);
}ADC_Chain_t;

void   ADC_voidInit(void);
void   ADC_voidEnable(void);
void   ADC_voidDisable(void);
uint8 ADC_u16StartConversionSynch(ADC_Channel_t  copy_eChannel,uint16* copy_pu16DigitalResult);
uint8 ADC_u16StartConversionASynch(ADC_Channel_t  copy_eChannel,uint16* copy_pu16DigitalResult, void (*copy_pfvNotificationFunc)(void));
uint8 ADC_u16StartChainConversionASynch(const ADC_Chain_t* copy_psChainObject);
uint16 ADC_u16GetAnalogVolt(uint16 copy_u16ADC_Reading);



#endif
