#ifndef 	ADC_CFG_H
#define 	ADC_CFG_H



/* configure reference selection, options: 		- A_REF
 * 										   		- A_VCC
 * 										   		- INTERNAL__2_56V
 * */
#define  ADC_u8REFRENCE					A_VCC



/* configure ADC RESOLUTION, options: 			- EIGHT_BITS
 * 												- TEN_BITS
 * */
#define  ADC_u8RESOLUTION				TEN_BITS


/* configure ADC PRESCALER, options: 			- DIV_BY_2
 * 												- DIV_BY_4
 * 												- DIV_BY_8
 * 												- DIV_BY_16
 * 												- DIV_BY_32
 * 												- DIV_BY_64
 * 												- DIV_BY_128
 * */
#define  ADC_u8PRESCALER				DIV_BY_128



/* configure time out for counter */
#define  ADC_u32TIMEOUT_COUNT 			5000UL



#endif
