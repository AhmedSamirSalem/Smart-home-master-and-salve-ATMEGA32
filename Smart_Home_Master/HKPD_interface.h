/**********************************/
/* Author :Ahmed Samir            */
/* SWC :KEYPAD                    */
/* Layer :HAL 		              */
/* Version :1.0                   */
/* Date :August 9,2023            */
/* Last Edit :N/A 	          	  */
/**********************************/

#ifndef _HKPD_INTERFACE_H_
#define _HKPD_INTERFACE_H_



/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: HKPD_charGetKey
*
*[Description]: This function is responsible for geeting  the pressed key in the keypad 
*				and return the value in respond to this button( you can chabge the value of each button in the config file)
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: char :return of the value of the pressed key
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/

char HKPD_charGetKey(void);



#endif
