/*
 * main.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Ahmed Samir
 */
//#include "util/delay.h"
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MDIO_interface.h"
#include "MADC_interface.h"
#include "MTIM_interface.h"
#include "MUART_interface.h"
#include "MGIE_interface.h"
#include "HLCD_interface.h"

void HOME_voidControlFan(void);
void OPEN_FAN(void);
void CLOSE_FAN(void);
void HOME_voidManualMode(void);
void HOME_voidAutoMode(void);
void HOME_voidExitAutoMode(void);
#define ADMIN_PASS 1234
#define MOTOR_PORT	MDIO_PORTD
#define MOTOR_PIN	MDIO_PIN7
char L_charOperation;
char L_charCallBackData;
int main(void)
{
	MDIO_StderrSetPinDirection(MOTOR_PORT,MOTOR_PIN,MDIO_PIN_OUTPUT);
	HLCD_voidinit();
	MADC_stderrInit(MADC_VREF_AVCC,MADC_PRESCALER_2);
	MADC_voidAdcEnable();
	MUART_stderrInit(9600,MUART_DATABITS_8,MUART_PARITY_NONE,MUART_STOPBITS_1);
	MUART_voidEnableRx();
	MGIE_voidEnable();
	L_charOperation=MUART_charReceiveChar();
	if(L_charOperation=='S')
	{
		HLCD_voidSendString("HELLO");
	}
	else
	{
		return 0;
	}
	while(1)
	{
		HLCD_voidSendCommand(HLCD_CLEAR);
		L_charOperation=MUART_charReceiveChar();
		if(L_charOperation=='M')
		{
			HOME_voidManualMode();
		}
		else if(L_charOperation=='A')
		{
			HOME_voidAutoMode();
		}
		else
		{

		}
	}
}

void HOME_voidManualMode(void)
{
	HLCD_voidSendCommand(HLCD_CLEAR);
	HLCD_voidSendString("Maunal Mode");
	while(1)
	{
		L_charOperation=MUART_charReceiveChar();
		if(L_charOperation=='F')
		{
			HOME_voidControlFan();
		}
		else if(L_charOperation=='B')
		{
			// go to main menu
			break;
		}
		else
		{
			// for now do nothing
		}
	}
}
void HOME_voidAutoMode(void)
{
	u32 L_u32Temp;
	u16 L_u16reading;
	HLCD_voidSendCommand(1);
	HLCD_voidSendString("Automatic Mode");
	MUART_stderrEnableInterrupt(MUART_INTERRUPT_RXC);
	while(1)
	{

		MUART_stderrSetCallback(HOME_voidExitAutoMode,MUART_INTERRUPT_RXC);
		if(L_charCallBackData!='B')
		{
			MADC_stderrRead(&L_u16reading,MADC_CHANNEL_ADC0);
			L_u32Temp=((u32)L_u16reading*5000)/256;
			L_u32Temp/=10;
			if(L_u32Temp>25)
			{
				OPEN_FAN();
			}
			else
			{
				CLOSE_FAN();
			}
		}
		else
		{
			MUART_stderrDisableInterrupt(MUART_INTERRUPT_RXC);
			break;
		}
	}


}
void HOME_voidControlFan(void)
{
	while(1)
	{
		L_charOperation=MUART_charReceiveChar();
		if(L_charOperation=='O')
		{
			HLCD_voidSendCommand(HLCD_CLEAR);
			HLCD_voidSendString("FAN ON");
			OPEN_FAN();
		}
		else if(L_charOperation=='F')
		{
			HLCD_voidSendCommand(HLCD_CLEAR);
			HLCD_voidSendString("FAN OFF");
			CLOSE_FAN();
		}
		else if(L_charOperation=='B')
		{
			break;
		}
		else
		{
			// for now do nothing
		}
	}
}

void OPEN_FAN(void)
{
	MDIO_StderrSetPinValue(MOTOR_PORT,MOTOR_PIN,MDIO_PIN_HIGH);
}
void CLOSE_FAN(void)
{
	MDIO_StderrSetPinValue(MOTOR_PORT,MOTOR_PIN,MDIO_PIN_LOW);
}
void HOME_voidExitAutoMode(void)
{
	L_charCallBackData=MUART_charReturnUDR();
}
