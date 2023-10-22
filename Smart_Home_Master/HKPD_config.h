/**********************************/
/* Author :Ahmed Samir            */
/* SWC :KEYPAD                    */
/* Layer :HAL 		              */
/* Version :1.0                   */
/* Date :August 9,2023            */
/* Last Edit :N/Ahmed 	          */
/**********************************/

#ifndef _HKPD_CONFIG_H_
#define _HKPD_CONFIG_H_

#define HKPD_PORT  MDIO_PORTB

char HKPD_charKeypad[4][4]={{'1','4','7','+'},
							{'2','5','8','-'},
							{'3','6','9','='},
							{'*','0','#','D'}};


#endif
