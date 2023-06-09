#ifndef	EXTI_REG_H
#define	EXTI_REG_H


#define MCUCR		*((volatile uint8*)0x55)	/*MCU ctrl register*/
#define MCUCR_ISC00		0u						/*Int. Sense Ctrl 0 bit 0*/
#define MCUCR_ISC01		1u						/*Int. Sense Ctrl 0 bit 1*/
#define MCUCR_ISC10		2u						/*Int. Sense Ctrl 1 bit 0*/
#define MCUCR_ISC11		3u						/*Int. Sense Ctrl 1 bit 1*/

#define MCUCSR		*((volatile uint8*)0x54)
#define MCUCSR_ISC2		6u


#define GICR		*((volatile uint8*)0x5B)
#define GICR_INT1		7u
#define GICR_INT0		6u
#define GICR_INT2		5u


#endif