#ifndef 	DCMOTOR_INTERFACE_H
#define 	DCMOTOR_INTERFACE_H



typedef struct
{
	DIO_Port_t DCMotor_Port;
	DIO_Pin_t  DCMotor_Pin1;
	DIO_Pin_t  DCMotor_Pin2;

}DCMotor_Config_t;


uint8 DCMotor_u8CW_Direction(const DCMotor_Config_t* copy_DCMotorObject);
uint8 DCMotor_u8CCW_Direction(const DCMotor_Config_t* copy_DCMotorObject);
uint8 DCMotor_u8Stop(const DCMotor_Config_t* copy_DCMotorObject);

#endif
