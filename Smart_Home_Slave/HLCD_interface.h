/**********************************/
/* Author :Ahmed Samir            */
/* SWC :LCD                       */
/* Layer :HAL 		              */
/* Version :1.3                   */
/* Date :August 9,2023            */
/* Last Edit :August 7,2023       */
/**********************************/

#ifndef _HLCD_INTERFACE_H_
#define _HLCD_INTERFACE_H_



#define HLCD_CLEAR 0x01
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidinit
*
*[Description]: This function is responsible for initalization of the LCD direction it takes the LCD_DATA_PORT and
*				LCD_CTRL_PORT macros in the config file and init them.(must set these macros before use this function)
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void HLCD_voidinit(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidSendChar
*
*[Description]: This function sends data to be shown on the lcd
*
*[Arguments]:
*
*[in]:  char ARG_charData: character to be shown in the lcd(ascii)
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void HLCD_voidSendChar(u8 ARG_u8Data);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidSendCommand
*
*[Description]: This function sends command to lcd( some of this command are defined macros in the interface file)
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Cmd: input to choose what command will be send to the lcd
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/

void HLCD_voidSendCommand(u8 ARG_u8Cmd);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidSendString
*
*[Description]: This function sends string to lcd
*
*[Arguments]:
*
*[in]:  const char *  ARG_charpString: pointer to the string that will be showed int the lcd
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void HLCD_voidSendString(const char * ARG_ccharpString);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidSendNumber
*
*[Description]: This function sends numbers to lcd
*
*[Arguments]:
*
*[in]:  s32 ARG_s32Number:  the number that will be showed int the lcd
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void HLCD_voidSendNumber(s32 ARG_s32Number);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidGoToXY
*
*[Description]: This function control the postion of the cursor postion of the lcd 
*
*[Arguments]:
*
*[in]:  u8 ARG_u8X:  the number of row of lcd (0 or 1)
*		u8 ARG_u8Y:	 the number of col of lcd (0 -> 15)
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void HLCD_voidGoToXY(u8 ARG_u8X,u8 ARG_u8Y);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidCustomChar
*
*[Description]: This function saves a custom character in the cgram the of the lcd
*
*[Arguments]:
*
*[in]:  u8 ARG_u8X:  the number of row of lcd (0 or 1)
*		u8 ARG_u8Y:	 the number of col of lcd (0 -> 15)
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/

void HLCD_voidCustomChar(u8 * ARG_u8pCustomChar,u8 ARG_u8CustomCharNum);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: LCD_voidSetCursor
*
*[Description]: This function control the postion of the cursor postion of the lcd 
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Row:  the number of row of lcd (0 or 1)
*		u8 ARG_u8Col:	 the number of col of lcd (0 -> 15)
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/

void HLCD_voidSetCursor(u8 ARG_u8Row,u8 ARG_u8Col);

#endif
