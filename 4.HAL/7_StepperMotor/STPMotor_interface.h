#ifndef 	STPMOTOR_INTERFACE_H
#define 	STPMOTOR_INTERFACE_H



typedef enum
{
	STPMotor_ClockWise,
	STPMotor_CounterClockWise
}STPMotor_Direction_t;

typedef struct
{
	DIO_Port_t 	STPMotor_Port;
	DIO_Pin_t	STPMotor_BluePin;
	DIO_Pin_t	STPMotor_PinkPin;
	DIO_Pin_t	STPMotor_YellowPin;
	DIO_Pin_t	STPMotor_OrangePin;
}STPMotor_Config_t;



uint8 STPMotor_u8Rotate(const STPMotor_Config_t* copy_STPMotorObject,STPMotor_Direction_t copy_STPMotorDirection,uint16 copy_u16Angle);



#endif
