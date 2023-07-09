#ifndef 	ADC_PRV_H
#define 	ADC_PRV_H


#define	  REFERENCE_MASK		0b00111111
#define   A_REF					0u
#define   A_VCC					1u
#define   INTERNAL__2_56V		3u



#define   EIGHT_BITS			1u
#define	  TEN_BITS              2u




#define	  PRESCALER_MASK		0b11111000
#define   DIV_BY_2				0u
#define   DIV_BY_4				2u
#define   DIV_BY_8				3u
#define   DIV_BY_16				4u
#define   DIV_BY_32				5u
#define   DIV_BY_64				6u
#define   DIV_BY_128			7u


#define	  CHANNEL_MASK			0b11100000

#define   IDLE					0u
#define   BUSY					1u

#define   SINGLE_CONVERSION  	0u
#define   CHAIN_CONVERSION  	1u


#define   FIRST_INDEX  			0u

#endif
