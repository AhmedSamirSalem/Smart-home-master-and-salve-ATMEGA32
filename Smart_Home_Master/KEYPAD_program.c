/***************************************************************/
/***************************************************************/
/********************** AUTHOR:  Ahmed Samir *******************/
/********************** LAYER:  HAL ***************************/
/********************** SWC:  KEYPAD ***************************/
/********************** VERSION:  1.00 *************************/
#include "LSTD_types.h"
#include"MDIO_interface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"
#include "util/delay.h"

u8 KEYPAD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey=KEYPAD_NoPressedKey;
	u8 Local_u8ColumnIndex,Local_u8rowIndex;

	static u8 Local_u8colArr[Keypad_colno]={KEYPAD_Col0Pin,KEYPAD_Col1Pin,KEYPAD_Col2Pin,KEYPAD_Col3Pin};
	static u8 Local_u8rowArr[Keypad_rowno]={KEYPAD_Row0Pin,KEYPAD_Row1Pin,KEYPAD_Row2Pin,KEYPAD_Row3Pin};

	static u8 Local_u8KEYPADArr[Keypad_rowno][Keypad_colno]=KEYPAD_Arr;

	for(Local_u8ColumnIndex=0;Local_u8ColumnIndex<Keypad_colno;Local_u8ColumnIndex++)
	{
		/*actve current colum*/
		MDIO_StderrSetPinValue(KEYPAD_Port,Local_u8colArr[Local_u8ColumnIndex],MDIO_PIN_LOW);
		for(Local_u8rowIndex=0;Local_u8rowIndex<Keypad_rowno;Local_u8rowIndex++)
		{
			if(DIO_u8GetPinValue(KEYPAD_Port,Local_u8rowArr[Local_u8rowIndex])==0)
			{
				Local_u8PressedKey=Local_u8KEYPADArr[Local_u8rowIndex][Local_u8ColumnIndex];
				while(DIO_u8GetPinValue(KEYPAD_Port,Local_u8rowArr[Local_u8rowIndex])==0){}
				_delay_ms(5);
				return Local_u8PressedKey;
			}
		}
		MDIO_StderrSetPinValue(KEYPAD_Port,Local_u8colArr[Local_u8ColumnIndex],MDIO_PIN_HIGH);
	}


	return Local_u8PressedKey;

}
