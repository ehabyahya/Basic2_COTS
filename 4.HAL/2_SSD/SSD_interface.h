#ifndef   	SSD_INTERFACE_H
#define   	SSD_INTERFACE_H


typedef enum
{
	SSD_CommonCasthod,
	SSD_CommonAnode,
	SSD_EtaKit
}SSD_Type_t;


typedef struct
{
	SSD_Type_t SSD_Type;
	DIO_Port_t SSD_Port;
	DIO_Pin_t  SSD_StartPin;
	DIO_Port_t SSD_EnablePort;
	DIO_Pin_t  SSD_EnablePin;
}SSD_Config_t;


uint8 SSD_u8SetNumber(const SSD_Config_t* copy_SSDObject,uint8 copy_u8Number);
uint8 SSD_u8Enable(const SSD_Config_t* copy_SSDObject);
uint8 SSD_u8Disable(const SSD_Config_t* copy_SSDObject);


#endif
