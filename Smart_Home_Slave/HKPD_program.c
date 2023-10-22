/**********************************/
/* Author :Ahmed Samir            */
/* SWC :KEYPAD                    */
/* Layer :HAL 		              */
/* Version :1.0                   */
/* Date :August 9,2023            */
/* Last Edit :N/Ahmed 	          */
/**********************************/

#include"LSTD_types.h"
#include"util/delay.h"
#include"MDIO_interface.h"
#include "HKPD_private.h"
#include "HKPD_config.h"
#include "HKPD_interface.h"

char HKPD_charGetKey(void)
{
	u8 L_u8Row,L_u8Col,L_u8Debounce=0;
	MDIO_StderrSetPortDirection(HKPD_PORT,0xF0);
	MDIO_StderrSetPortValue(HKPD_PORT,0x0F);
	do
	{
		MDIO_StderrGetPortValue(&L_u8Row,HKPD_PORT);
		L_u8Row=(~L_u8Row)&0X0F;
	}while(L_u8Row==0X00);
	MDIO_StderrSetPortDirection(HKPD_PORT,0x0F);
	MDIO_StderrSetPortValue(HKPD_PORT,0xF0);
	MDIO_StderrGetPortValue(&L_u8Col,HKPD_PORT);
	L_u8Col=(((~L_u8Col)&0XF0)>>4);
	while(L_u8Debounce!=0xF0)
	{
		MDIO_StderrGetPortValue(&L_u8Debounce,HKPD_PORT);
		//HLCD_voidSendNumber(L_u8Debounce);
	}
	_delay_ms(10);
	switch(L_u8Row)
	{
		case 1:L_u8Row=0;break;
		case 2:L_u8Row=1;break;
		case 4:L_u8Row=2;break;
		case 8:L_u8Row=3;break;
		default:break;//do nothing
	}
	switch(L_u8Col)
	{
		case 1:L_u8Col=0;break;
		case 2:L_u8Col=1;break;
		case 4:L_u8Col=2;break;
		case 8:L_u8Col=3;break;
		default:break;//do nothing
	}
	return HKPD_charKeypad[L_u8Row][L_u8Col];


}
