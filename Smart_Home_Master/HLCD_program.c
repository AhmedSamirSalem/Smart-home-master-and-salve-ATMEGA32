/**********************************/
/* Author :Ahmed Samir            */
/* SWC :LCD                       */
/* Layer :HAL 		              */
/* Version :1.3                   */
/* Date :August 9,2023            */
/* Last Edit :August 7,2023       */
/**********************************/
#include"util/delay.h"
#include"LSTD_types.h"
#include"MDIO_interface.h"
#include "MTIM_interface.h"
#include "HLCD_private.h"
#include "HLCD_config.h"
#include "HLCD_interface.h"


void HLCD_voidinit(void)
{

#if HLCD_MODE==HLCD_8BIT_MODE
	MDIO_StderrSetPortDirection(HLCD_DATA_PORT,0xFF);
	MDIO_StderrSetPinDirection(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_OUTPUT);
	HLCD_voidSendCommand(HLCD_FUNCTION_SET);
	MTIM_voidBusyWaitDlay(1);
	HLCD_voidSendCommand(HLCD_DISPLAY_ON_OFF);
	MTIM_voidBusyWaitDlay(1);
	HLCD_voidSendCommand(HLCD_CLEAR);
	MTIM_voidBusyWaitDlay(2);
#elif HLCD_MODE==HLCD_4BIT_MODE
	MDIO_StderrSetPinDirection(HLCD_DATA_PORT,HLCD_DB4_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_DATA_PORT,HLCD_DB5_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_DATA_PORT,HLCD_DB6_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_DATA_PORT,HLCD_DB7_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_PIN_OUTPUT);
	MDIO_StderrSetPinDirection(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_OUTPUT);
	HLCD_voidSendCommand(0X2C);
	_delay_us(50);
	HLCD_voidSendCommand(HLCD_DISPLAY_ON_OFF);
	_delay_us(50);
	HLCD_voidSendCommand(HLCD_CLEAR);
	_delay_ms(2);

#endif
}
void HLCD_voidSendChar(u8 ARG_u8Data)
{
#if HLCD_MODE==HLCD_8BIT_MODE
	/* control*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_PIN_HIGH);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPortValue(HLCD_DATA_PORT,ARG_u8Data);
	/* enable cycle*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_HIGH);
	MTIM_voidBusyWaitDlay(2);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
#elif HLCD_MODE==HLCD_4BIT_MODE
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_PIN_HIGH);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB4_PIN,(ARG_u8Data>>4)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB5_PIN,(ARG_u8Data>>5)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB6_PIN,(ARG_u8Data>>6)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB7_PIN,(ARG_u8Data>>7)&1);
	/* enable cycle*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_HIGH);
	_delay_ms(2);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB4_PIN,(ARG_u8Data>>0)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB5_PIN,(ARG_u8Data>>1)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB6_PIN,(ARG_u8Data>>2)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB7_PIN,(ARG_u8Data>>3)&1);
	/* enable cycle*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_HIGH);
	_delay_ms(2);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
#endif

}
void HLCD_voidSendCommand(u8 ARG_u8Cmd)
{
#if HLCD_MODE==HLCD_8BIT_MODE
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPortValue(HLCD_DATA_PORT,ARG_u8Cmd);
	/* enable cycle*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_HIGH);
	MTIM_voidBusyWaitDlay(2);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
#elif HLCD_MODE==HLCD_4BIT_MODE
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RS_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_RW_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB4_PIN,(ARG_u8Cmd>>4)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB5_PIN,(ARG_u8Cmd>>5)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB6_PIN,(ARG_u8Cmd>>6)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB7_PIN,(ARG_u8Cmd>>7)&1);

	/* enable cycle*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_HIGH);
	_delay_ms(2);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB4_PIN,(ARG_u8Cmd>>0)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB5_PIN,(ARG_u8Cmd>>1)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB6_PIN,(ARG_u8Cmd>>2)&1);
	MDIO_StderrSetPinValue(HLCD_DATA_PORT,HLCD_DB7_PIN,(ARG_u8Cmd>>3)&1);

	/* enable cycle*/
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_HIGH);
	_delay_ms(2);
	MDIO_StderrSetPinValue(HLCD_CTRL_PORT,HLCD_E_PIN,MDIO_PIN_LOW);


#endif
}
void HLCD_voidSendString(const char * ARG_charpString)
{
	u8 Local_u8Counter=0;
	if(ARG_charpString!=NULL)
	{
		while(ARG_charpString[Local_u8Counter]!='\0')
		{
			HLCD_voidSendChar(ARG_charpString[Local_u8Counter]);
			Local_u8Counter++;
			if(Local_u8Counter==16)
			{
				HLCD_voidGoToXY(1,0);
			}
			else
			{
				//do nothing
			}
		}

	}
	else
	{
		// do nothing
	}
}

void HLCD_voidSendNumber(s32 ARG_s32Number)
{
	u8 Local_u8Arr[10],Local_u8Counter=0;
	if(ARG_s32Number<0)
	{
		HLCD_voidSendChar('-');
		ARG_s32Number*=-1;
	}
	else if(0==ARG_s32Number)
	{
		HLCD_voidSendChar('0');
	}
	else
	{
		// do nothing
	}
	while(ARG_s32Number)
	{
		Local_u8Arr[Local_u8Counter]=ARG_s32Number%10;
		ARG_s32Number/=10;
		Local_u8Counter++;
	}
	while(Local_u8Counter>0)
	{
		Local_u8Counter--;
		HLCD_voidSendChar('0'+Local_u8Arr[Local_u8Counter]);
	}
}
void HLCD_voidGoToXY(u8 ARG_u8X,u8 ARG_u8Y)
{
	u8 Local_u8Addres;
	if(0==ARG_u8X)
	{
		Local_u8Addres=ARG_u8Y;
	}
	else if(1==ARG_u8X)
	{
		Local_u8Addres=ARG_u8Y+DDRAM_ROW_OFFSET; // offset of the ddram addres
	}
	else
	{
		// Report an error
	}
	HLCD_voidSendCommand(Local_u8Addres+DDRAM_ADDRESS_OFFSET);// for setting ddram addres send(1 d6 d5 d4 d3 d2 d1 d0) or 128+the postion you want

}
void HLCD_voidCustomChar(u8 * ARG_u8pCustomChar,u8 ARG_u8CustomCharNum)
{
	u8 Local_u8Counter;
	// seeting the address of the cgram to save the custom character
	u8 Local_u8CGRAMAddres=ARG_u8CustomCharNum*8;
	HLCD_voidSendCommand(Local_u8CGRAMAddres+64);// for setting ddram addres send(1 d6 d5 d4 d3 d2 d1 d0) or 128+the postion you want
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		HLCD_voidSendChar(ARG_u8pCustomChar[Local_u8Counter]);
	}
	// get back to ddram
	HLCD_voidSendCommand(DDRAM_ADDRESS_OFFSET);



}
void HLCD_voidSetCursor(u8 ARG_u8Row,u8 ARG_u8Col)
{
	HLCD_voidSendCommand((((4*ARG_u8Row)<<4)+0x80+ARG_u8Col));
}
