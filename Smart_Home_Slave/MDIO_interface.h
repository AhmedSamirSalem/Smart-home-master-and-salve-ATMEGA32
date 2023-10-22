/**********************************/
/**********************************/
/* Author :Ahmed Samir            */
/* SWC :DIO                       */
/* Layer :MCAL 		              */
/* Version :1.1                   */
/* Date :August 3,2023            */
/* Last Edit :August 2,2023       */
/**********************************/

#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_


#define MDIO_PORTA  1
#define MDIO_PORTB  2
#define MDIO_PORTC  3
#define MDIO_PORTD  4

#define MDIO_PIN_OUTPUT  1
#define MDIO_PIN_INPUT   2
#define MDIO_PIN_PULLUP  3

#define MDIO_PIN_HIGH 1
#define MDIO_PIN_LOW 0



#define MDIO_PIN0  	0
#define MDIO_PIN1  	1
#define MDIO_PIN2  	2
#define MDIO_PIN3  	3
#define MDIO_PIN4  	4
#define MDIO_PIN5  	5
#define MDIO_PIN6  	6
#define MDIO_PIN7  	7

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
STD_error_t MDIO_StderrSetPortDirection(u8 ARG_u8Port, u8 ARG_u8Direction);

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

STD_error_t MDIO_StderrSetPortValue(u8 ARG_u8Port, u8 ARG_u8Value);



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
STD_error_t MDIO_StderrGetPortValue(u8 * ARG_u8pValue,u8 ARG_u8Port);


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

STD_error_t MDIO_StderrSetPinDirection(u8 ARG_u8Port,u8 ARG_u8Pin, u8 ARG_u8Direction);

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

STD_error_t MDIO_StderrSetPinValue(u8 ARG_u8Port,u8 ARG_u8Pin, u8 ARG_u8Value);

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
STD_error_t MDIO_StderrTogglePinValue(u8 ARG_u8Port,u8 ARG_u8Pin);


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
STD_error_t MDIO_StderrGetPinValue(u8 * ARG_u8pValue,u8 ARG_u8Port,u8 ARG_u8Pin);




u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);

#endif
