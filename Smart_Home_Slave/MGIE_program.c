/**********************************/
/* Author :Ahmed Samir            */
/* SWC :GIE	                  	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 12,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#include "LSTD_types.h"
#include "LBIT_math.h"

#include "MGIE_private.h"
#include "MGIE_interface.h"


void MGIE_voidEnable(void)
{
	SET_BIT(SREG,I);
}
void MGIE_voidDisable(void)
{
	CLEAR_BIT(SREG,I);
}
