/**********************************/
/* Author :Ahmed Samir            */
/* SWC :DIO                       */
/* Layer :MCAL 		              */
/* Version :1.1                   */
/* Date :August 3,2023            */
/* Last Edit :August 2,2023       */
/**********************************/

/* Library Includes */
#include"LSTD_types.h"
#include"LBIT_math.h"

/* SWC Includes */

#include"MDIO_private.h"
#include"MDIO_interface.h"


/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrSetPortDirection
*
*[Description]: This function is responsible for Setting the direction for port (input,output)
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 ARG_u8Direction  :   This Argument indicates the required direction
*
*[out]: N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/

STD_error_t MDIO_StderrSetPortDirection(u8 ARG_u8Port, u8 ARG_u8Direction)
{
	STD_error_t L_StderrError=E_OK;
	switch(ARG_u8Port)
	{
		case MDIO_PORTA:GPIOA -> DDR=ARG_u8Direction;break;
		case MDIO_PORTB:GPIOB -> DDR=ARG_u8Direction;break;
		case MDIO_PORTC:GPIOC -> DDR=ARG_u8Direction;break;
		case MDIO_PORTD:GPIOD -> DDR=ARG_u8Direction;break;
		default:L_StderrError=E_NOK;break;/*Report an Error */
	}
	return L_StderrError;
}

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrSetPortValue
*
*[Description]: This function is responsible for writing values in port (High,Low)
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:			This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 ARG_u8Value  :   	This Argument indicates the required value to be written
*
*[out]: N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/
STD_error_t MDIO_StderrSetPortValue(u8 ARG_u8Port, u8 ARG_u8Value)
{
	STD_error_t L_StderrError=E_OK;
	switch(ARG_u8Port)
	{
		case MDIO_PORTA:GPIOA -> PORT=ARG_u8Value;break;
		case MDIO_PORTB:GPIOB -> PORT=ARG_u8Value;break;
		case MDIO_PORTC:GPIOC -> PORT=ARG_u8Value;break;
		case MDIO_PORTD:GPIOD -> PORT=ARG_u8Value;break;
		default:L_StderrError=E_NOK;break;/*Report an Error */
	}
	return L_StderrError;
}

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrGetPortValue
*
*[Description]: This function is responsible for get the  values in port (High,Low)
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:			This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 * ARG_u8pValue  :   	This Argument used to return value in pin register 
*
*[out]:	u8 * ARG_u8pValue :     This Argument used to return value in pin register
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/
STD_error_t MDIO_StderrGetPortValue(u8 * ARG_u8pValue,u8 ARG_u8Port)
{
	STD_error_t L_StderrError=E_OK;
	if(NULL==ARG_u8pValue)
	{
		L_StderrError=E_NULL_POINTER;
	}
	else
	{
		switch(ARG_u8Port)
		{
			case MDIO_PORTA:*ARG_u8pValue=GPIOA -> PIN;break;
			case MDIO_PORTB:*ARG_u8pValue=GPIOB ->  PIN;break;
			case MDIO_PORTC:*ARG_u8pValue=GPIOC ->PIN ;break;
			case MDIO_PORTD:*ARG_u8pValue=GPIOD ->PIN ;break;
			default:L_StderrError=E_NOK;break;/*Report an Error */
		}
	}
	return L_StderrError;

}
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrSetPinDirection
*
*[Description]: This function is responsible for setting the direction of one pin at specific port(input ,output,pullup)
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:			This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 ARG_u8Pin  :   	    This Argument indicates the required pin (MDIO_PIN0->MDIO_PIN7)
*		u8 ARG_u8Direction:     This Argument indicates the required direction(input ,output,pullup)
*
*[out]:	N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/

STD_error_t MDIO_StderrSetPinDirection(u8 ARG_u8Port,u8 ARG_u8Pin, u8 ARG_u8Direction)
{
	STD_error_t L_StderrError=E_OK;
	if((ARG_u8Pin>=0)&&(ARG_u8Pin<=7))
	{
		if(MDIO_PIN_OUTPUT==ARG_u8Direction)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA:SET_BIT(GPIOA -> DDR,ARG_u8Pin);break;
				case MDIO_PORTB:SET_BIT(GPIOB -> DDR,ARG_u8Pin);break;
				case MDIO_PORTC:SET_BIT(GPIOC -> DDR,ARG_u8Pin);break;
				case MDIO_PORTD:SET_BIT(GPIOD -> DDR,ARG_u8Pin);break;
				default:L_StderrError=E_NOK;break;/*Report an Error */
			}
		}
		else if(MDIO_PIN_INPUT==ARG_u8Direction)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA:CLEAR_BIT(GPIOA -> DDR,ARG_u8Pin);break;
				case MDIO_PORTB:CLEAR_BIT(GPIOB -> DDR,ARG_u8Pin);break;
				case MDIO_PORTC:CLEAR_BIT(GPIOC -> DDR,ARG_u8Pin);break;
				case MDIO_PORTD:CLEAR_BIT(GPIOD -> DDR,ARG_u8Pin);break;
				default:L_StderrError=E_NOK;break;/*Report an Error */
			}
		}
		else if(MDIO_PIN_PULLUP==ARG_u8Direction)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA:CLEAR_BIT(GPIOA -> DDR,ARG_u8Pin);SET_BIT(GPIOA -> PORT,ARG_u8Pin);break;
				case MDIO_PORTB:CLEAR_BIT(GPIOB -> DDR,ARG_u8Pin);SET_BIT(GPIOB -> PORT,ARG_u8Pin);break;
				case MDIO_PORTC:CLEAR_BIT(GPIOC -> DDR,ARG_u8Pin);SET_BIT(GPIOC -> PORT,ARG_u8Pin);break;
				case MDIO_PORTD:CLEAR_BIT(GPIOD -> DDR,ARG_u8Pin);SET_BIT(GPIOD -> PORT,ARG_u8Pin);break;
				default:L_StderrError=E_NOK;break;/*Report an Error */
			}
		}
		else
		{
			L_StderrError=E_NOK;
		}
	}
	else
	{
		L_StderrError=E_NOK;
	}
	return L_StderrError;
}

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrSetPinValue
*
*[Description]: This function is responsible for setting the value of one pin at specific port(High ,Low)
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:			This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 ARG_u8Pin  :   	    This Argument indicates the required pin (MDIO_PIN0->MDIO_PIN7)
*		u8 ARG_u8Value:     This Argument indicates the required Value     (High ,Low)
*
*[out]:	N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/
STD_error_t MDIO_StderrSetPinValue(u8 ARG_u8Port,u8 ARG_u8Pin, u8 ARG_u8Value)
{
	STD_error_t L_StderrError=E_OK;
	if((ARG_u8Pin>=0)&&(ARG_u8Pin<=7))
	{
		if(MDIO_PIN_HIGH==ARG_u8Value)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA:SET_BIT(GPIOA -> PORT,ARG_u8Pin);break;
				case MDIO_PORTB:SET_BIT(GPIOB -> PORT,ARG_u8Pin);break;
				case MDIO_PORTC:SET_BIT(GPIOC -> PORT,ARG_u8Pin);break;
				case MDIO_PORTD:SET_BIT(GPIOD -> PORT,ARG_u8Pin);break;
				default:L_StderrError=E_NOK;break;/*Report an Error */
			}
		}
		else if(MDIO_PIN_LOW==ARG_u8Value)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA:CLEAR_BIT(GPIOA -> PORT,ARG_u8Pin);break;
				case MDIO_PORTB:CLEAR_BIT(GPIOB -> PORT,ARG_u8Pin);break;
				case MDIO_PORTC:CLEAR_BIT(GPIOC -> PORT,ARG_u8Pin);break;
				case MDIO_PORTD:CLEAR_BIT(GPIOD -> PORT,ARG_u8Pin);break;
				default:L_StderrError=E_NOK;break;/*Report an Error */
			}
		}
		else
		{
			L_StderrError=E_NOK;
		}
	}
	else
	{
		L_StderrError=E_NOK;
	}
	return L_StderrError;
}

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrTogglePinValue
*
*[Description]: This function is responsible for togglig the value of one pin at specific port
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:			This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 ARG_u8Pin  :   	    This Argument indicates the required pin (MDIO_PIN0->MDIO_PIN7)
*		
*
*[out]:	N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/

STD_error_t MDIO_StderrTogglePinValue(u8 ARG_u8Port,u8 ARG_u8Pin)
{
	STD_error_t L_StderrError=E_OK;
	if((ARG_u8Pin>=0)&&(ARG_u8Pin<=7))
	{
		switch(ARG_u8Port)
		{
			case MDIO_PORTA:TOGGLE_BIT(GPIOA -> PORT,ARG_u8Pin);break;
			case MDIO_PORTB:TOGGLE_BIT(GPIOB -> PORT,ARG_u8Pin);break;
			case MDIO_PORTC:TOGGLE_BIT(GPIOC -> PORT,ARG_u8Pin);break;
			case MDIO_PORTD:TOGGLE_BIT(GPIOD -> PORT,ARG_u8Pin);break;
			default:L_StderrError=E_NOK;break;/*Report an Error */
		}
	}
	else
	{
		L_StderrError=E_NOK;
	}
	return L_StderrError; 	
}


/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MDIO_StderrGetPinValue
*
*[Description]: This function is responsible for getting the value of one pin at specific port
*
*[Arguments]:
*
*[in]:  u8 ARG_u8Port:			This Argument indicates the required port (MDIO_PORTA,MDIO_PORTB,MDIO_PORTC,MDIO_PORTD)
*       u8 ARG_u8Pin  :   	    This Argument indicates the required pin (MDIO_PIN0->MDIO_PIN7)
*		u8 * ARG_u8pValue:      This Argument used to return the value of the required pin
*
*[out]: u8 * ARG_u8pValue
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/
STD_error_t MDIO_StderrGetPinValue(u8 * ARG_u8pValue,u8 ARG_u8Port,u8 ARG_u8Pin)
{	
	STD_error_t L_StderrError=E_OK;
	if(NULL==ARG_u8pValue)
	{
		L_StderrError=E_NULL_POINTER;
	}
	else
	{
		switch(ARG_u8Port)
		{
			case MDIO_PORTA:*ARG_u8pValue=GET_BIT(GPIOA -> PIN,ARG_u8Pin);break;
			case MDIO_PORTB:*ARG_u8pValue=GET_BIT(GPIOB -> PIN,ARG_u8Pin);break;
			case MDIO_PORTC:*ARG_u8pValue=GET_BIT(GPIOC -> PIN,ARG_u8Pin);break;
			case MDIO_PORTD:*ARG_u8pValue=GET_BIT(GPIOD -> PIN,ARG_u8Pin);break;
			default:L_StderrError=E_NOK;break;/*Report an Error */
		}
	}
	return L_StderrError;
}






u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_result;
	if(Copy_u8Pin<=MDIO_PIN7)
	{
		switch(Copy_u8Port)
		{
		case MDIO_PORTA:Local_result=GET_BIT(GPIOA -> PIN,Copy_u8Pin);break;
		case MDIO_PORTB:Local_result=GET_BIT(GPIOB -> PIN,Copy_u8Pin);break;
		case MDIO_PORTC:Local_result=GET_BIT(GPIOC -> PIN,Copy_u8Pin);break;
		case MDIO_PORTD:Local_result=GET_BIT(GPIOD -> PIN,Copy_u8Pin);break;
		}
	}
	return Local_result;
}
