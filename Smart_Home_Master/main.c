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
#include "HLCD_interface.h"
#include "HKPD_interface.h"
#include "HNVM_interface.h"
#include "KEYPAD_interface.h"

u8 HOME_u8GetPassword(void);
void HOME_voidEditPassword(void);
void HOME_voidManualMode(void);
void HOME_voidControlFan(void);
void OPEN_FAN(void);
void CLOSE_FAN(void);
void OPEN_DOOR(void);
void CLOSE_DOOR(void);
void HOME_voidAutoMode(void);
#define ADMIN_PASS 123
#define MOTOR_PORT	MDIO_PORTD
#define MOTOR_PIN	MDIO_PIN7
#define DOOR_PORT	MDIO_PORTD
#define DOOR_PIN	MDIO_PIN5
#define SCL_PIN		MDIO_PIN0
#define SDA_PIN		MDIO_PIN1
#define PASS_LOCATION	0x22

int main(void)
{

	/* key pad init */
	MDIO_StderrSetPortDirection(MDIO_PORTB,0x0F);
	MDIO_StderrSetPortValue(MDIO_PORTB,0xF0);
	/* Motor init*/
	MDIO_StderrSetPinDirection(MOTOR_PORT,MOTOR_PIN,MDIO_PIN_OUTPUT);
	/* Door init*/
	MDIO_StderrSetPinDirection(DOOR_PORT,DOOR_PIN,MDIO_PIN_OUTPUT);
	/* SDA ,SCL init */
	MDIO_StderrSetPinDirection(MDIO_PORTC,SCL_PIN,MDIO_PIN_PULLUP);
	MDIO_StderrSetPinDirection(MDIO_PORTC,SCL_PIN,MDIO_PIN_PULLUP);
	/* set timer 1 to fast pwm mode with top value of 20000 and tick count equal to 1us to make pulse freq =20ms*/
	MTIM_stderrInit(MTIM_TIMER1,MTIM_CS_CLOCK_PRESCALAR_8,MTIM_MODE_FASTPWMCTRLTOP,MTIM_HWPIN_NONINVERTING_PWM);
	MTIM_SetTimer1TopValue(20000);
	HLCD_voidinit();
	MADC_stderrInit(MADC_VREF_AVCC,MADC_PRESCALER_2);
	MADC_voidAdcEnable();
	MUART_stderrInit(9600,MUART_DATABITS_8,MUART_PARITY_NONE,MUART_STOPBITS_1);
	MUART_voidEnableTx();
	HNVM_stderrInit();
	HLCD_voidSendString("HELLO");
	MTIM_voidBusyWaitDlay(2500);
	u8 L_u8PassFlag=1;
	u8 L_u8HomeMode;
	while(1)
	{
		L_u8PassFlag=HOME_u8GetPassword();
		if(1==L_u8PassFlag)
		{
			MUART_voidSendChar('S');
			OPEN_DOOR();
			HLCD_voidSendCommand(1);
			HLCD_voidSendString("1-Control Home");
			HLCD_voidGoToXY(1,0);
			HLCD_voidSendString("2-Edit Password");
			L_u8HomeMode=KEYPAD_u8GetPressedKey();
			while(L_u8HomeMode==255)
			{
				L_u8HomeMode=KEYPAD_u8GetPressedKey();
			}
			if(2==L_u8HomeMode)
			{
				HOME_voidEditPassword();
			}
			else
			{
				// do nothing countiue to execute control home program
			}
			while(1)
			{
				HLCD_voidSendCommand(1);
				HLCD_voidSendString("choose mode:");
				HLCD_voidGoToXY(1,0);
				HLCD_voidSendString("1- Manual 2-Auto");
				L_u8HomeMode=KEYPAD_u8GetPressedKey();
				while(L_u8HomeMode==255)
				{
					L_u8HomeMode=KEYPAD_u8GetPressedKey();
				}
				if(1==L_u8HomeMode)
				{
					MUART_voidSendChar('M');
					HOME_voidManualMode();
				}
				else if(2==L_u8HomeMode)
				{
					MUART_voidSendChar('A');
					HOME_voidAutoMode();
				}
				else
				{
					// do nothing
				}
			}

		}
		else
		{
			HLCD_voidSendCommand(1);
			HLCD_voidSendString("Theif Call 911");
			HLCD_voidGoToXY(1,0);
			HLCD_voidSendString("Door is closed");
			CLOSE_DOOR();
			break;
		}
	}
	return 0;
}

u8 HOME_u8GetPassword(void)
{
	u8 L_u8read;
	u8 L_u8PassCounter;
	u8 L_u8EnteredPass=0;
	u8 L_u8LoginPass=0;
	u8 L_u8PassFlag=0;

	for(L_u8PassCounter=0;L_u8PassCounter<3;L_u8PassCounter++)
	{
		HLCD_voidSendCommand(1);
		HLCD_voidSendString("Enter Pass:");
		L_u8EnteredPass=0;
		L_u8LoginPass=0;
		while(L_u8EnteredPass<3)
		{
			L_u8read=KEYPAD_u8GetPressedKey();
			if(L_u8read!=255)
			{
				HLCD_voidSendChar('*');
				L_u8LoginPass=L_u8LoginPass*10+L_u8read;
				L_u8EnteredPass++;
			}
		}
		L_u8read=HNVM_u8ReadByte(PASS_LOCATION);
		if(L_u8read==0)
		{
			//default
			// for the first time only if the user changes the pass this will never be with zero
			L_u8read=123;
		}
		else
		{
			//
		}
		if(L_u8read==L_u8LoginPass)
		{
			HLCD_voidSendCommand(1);
			HLCD_voidSendString("Welcome Ahmed");
			L_u8PassFlag=1;
			MTIM_voidBusyWaitDlay(500);
			break;
		}
		else
		{
			HLCD_voidSendCommand(1);
			HLCD_voidSendString("Wrong pass");
			HLCD_voidGoToXY(1,0);
			HLCD_voidSendNumber(2-L_u8PassCounter);
			HLCD_voidSendString("More try");
			MTIM_voidBusyWaitDlay(1500);
		}
	}
	return L_u8PassFlag;
}
void HOME_voidEditPassword(void)
{
	u8 L_u8read;
	u8 L_u8EnteredPass=0;
	u8 L_u8NewLoginPass=0;
	u8 L_u8ConforimNewPass=0;

	HLCD_voidSendCommand(1);
	HLCD_voidSendString("Enter New Pass:");
	HLCD_voidGoToXY(1,0);
	L_u8EnteredPass=0;
	L_u8NewLoginPass=0;
	while(L_u8EnteredPass<3)
	{
		L_u8read=KEYPAD_u8GetPressedKey();
		if(L_u8read!=255)
		{
			HLCD_voidSendChar('*');
			L_u8NewLoginPass=L_u8NewLoginPass*10+L_u8read;
			L_u8EnteredPass++;
		}
	}
	HLCD_voidSendCommand(HLCD_CLEAR);
	HLCD_voidSendString("Confirm Pass:");
	HLCD_voidGoToXY(1,0);
	L_u8EnteredPass=0;
	L_u8ConforimNewPass=0;
	while(L_u8EnteredPass<3)
	{
		L_u8read=KEYPAD_u8GetPressedKey();
		if(L_u8read!=255)
		{
			HLCD_voidSendChar('*');
			L_u8ConforimNewPass=L_u8ConforimNewPass*10+L_u8read;
			L_u8EnteredPass++;
		}
	}
	if(L_u8ConforimNewPass==L_u8NewLoginPass)
	{
		HNVM_voidWriteByte(PASS_LOCATION,L_u8NewLoginPass);
		HLCD_voidSendString("Password Changed");
		MTIM_voidBusyWaitDlay(1000);

	}
	else
	{
		HLCD_voidSendString("not same pass");
		MTIM_voidBusyWaitDlay(1000);
	}
}
void HOME_voidManualMode(void)
{
	u8 L_u8Device;
	while(1)
	{

		L_u8Device=255;
		HLCD_voidSendCommand(1);
		HLCD_voidSendString("1- Contol Fan");
		HLCD_voidGoToXY(1,0);
		HLCD_voidSendString("3- to go back");
		while(L_u8Device==255)
		{
			L_u8Device=KEYPAD_u8GetPressedKey();
		}
		if(L_u8Device!=255)
		{
			if(1==L_u8Device)
			{
				MUART_voidSendChar('F');
				HOME_voidControlFan();
			}
			else if(2==L_u8Device)
			{

			}
			else if(3==L_u8Device)
			{
				MUART_voidSendChar('B');
				break;
				// do nothing
			}
		}
	}
}
void HOME_voidAutoMode(void)
{
	u8 L_u8Device;
	HLCD_voidSendCommand(1);
	HLCD_voidSendString("Automatic Mode");
	HLCD_voidGoToXY(1,0);
	HLCD_voidSendString("3-to go back");
	while(1)
	{
		L_u8Device=KEYPAD_u8GetPressedKey();
		if(3==L_u8Device)
		{
			MUART_voidSendChar('B');
			break;
		}
	}
}
void HOME_voidControlFan(void)
{
	HLCD_voidSendCommand(1);
	HLCD_voidSendString("1- ON 2-OFF");
	HLCD_voidGoToXY(1,0);
	HLCD_voidSendString("3- to go back");
	u8 L_u8State;
	while(1)
	{
		L_u8State=KEYPAD_u8GetPressedKey();
		if(L_u8State!=255)
		{
			if(1==L_u8State)
			{
				MUART_voidSendChar('O');
			}
			else if(2==L_u8State)
			{
				MUART_voidSendChar('F');
			}
			else if(3==L_u8State)
			{
				MUART_voidSendChar('B');
				break;
			}
			else
			{
				// do nothing
			}
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
void OPEN_DOOR(void)
{
	u16 L_u8Counter;
	MTIM_stderrStartTimer(MTIM_TIMER1);
	for(L_u8Counter=1500;L_u8Counter<=2000;L_u8Counter++)
	{
		MTIM_stderrSetOCR(MTIM_TIMER1,L_u8Counter);
		MTIM_voidBusyWaitDlay(5);
	}
	MTIM_stderrStopTimer(MTIM_TIMER1);

}
void CLOSE_DOOR(void)
{
	u16 L_u8Counter;
	MTIM_stderrStartTimer(MTIM_TIMER1);
	for(L_u8Counter=1500;L_u8Counter>=1000;L_u8Counter--)
	{
		MTIM_stderrSetOCR(MTIM_TIMER1,L_u8Counter);
		MTIM_voidBusyWaitDlay(5);
	}
	MTIM_stderrStopTimer(MTIM_TIMER1);
}
