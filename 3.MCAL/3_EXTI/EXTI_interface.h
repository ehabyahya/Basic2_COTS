#ifndef	EXTI_INTERFACE_H
#define	EXTI_INTERFACE_H



typedef enum
{
	LOW_LEVEL=0,
	ON_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}EXTI_SenseCtrl_t;

typedef enum
{
	INT0,
	INT1,
	INT2
}EXTI_IntNUM_t;


voidEXTI_voidInit(void);

uint8 EXTI_u8SetSenseCtrl(EXTI_IntNUM_t copy_IntNUM,EXTI_SenseCtrl_t copy_SenseCtrl);

uint8 EXTI_u8InntEnable(EXTI_IntNUM_t copy_IntNUM);
uint8 EXTI_u8IntDisable(EXTI_IntNUM_t copy_IntNUM);







#endif