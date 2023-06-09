#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H




typedef enum
{
	LED_ACTIVE_HIGH,
	LED_ACTIVE_LOW

}LED_Activity_t;


typedef struct
{
	DIO_Port_t LED_PORT;
	DIO_Pin_t LED_PIN;
	LED_Activity_t LED_ACTIVITY;
}LED_Config_t;


uint8 LED_u8ON(const LED_Config_t* copy_LEDObject);
uint8 LED_u8OFF(const LED_Config_t* copy_LEDObject);
uint8 LED_u8TOGGLE(const LED_Config_t* copy_LEDObject);





#endif
