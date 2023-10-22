/**********************************/
/* Author :Ahmed Samir            */
/* SWC :LCD                       */
/* Layer :HAL 		              */
/* Version :1.3                   */
/* Date :August 9,2023            */
/* Last Edit :August 7,2023       */
/**********************************/

#ifndef _HLCD_CONFIG_H_
#define _HLCD_CONFIG_H_


#define HLCD_DATA_PORT   MDIO_PORTA  //(MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
#define HLCD_CTRL_PORT	MDIO_PORTD  //(MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
#define HLCD_RS_PIN  	MDIO_PIN0   //(MDIO_PIN0->MDIO_PIN7)
#define HLCD_RW_PIN  	MDIO_PIN2
#define HLCD_E_PIN  		MDIO_PIN3


#define HLCD_FUNCTION_SET  	0x3C //(data_length=8,no_of_lines=2,font_type=5x10)
#define HLCD_DISPLAY_ON_OFF  0x0F //(set_display,set_cursor,set_cursor_blinking)

#define DDRAM_ADDRESS_OFFSET	0x80
#define DDRAM_ROW_OFFSET    	0x40



#define HLCD_MODE	HLCD_8BIT_MODE	//HLCD_4BIT_MODE,HLCD_8BIT_MODE
#define HLCD_DB4_PIN	MDIO_PIN4
#define HLCD_DB5_PIN	MDIO_PIN5
#define HLCD_DB6_PIN	MDIO_PIN6
#define HLCD_DB7_PIN	MDIO_PIN7


#endif
