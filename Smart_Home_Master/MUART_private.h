/**********************************/
/* Author :Ahmed Samir            */
/* SWC :TIMER0	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 23,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MUART_PRIVATE_H_
#define	_MUART_PRIVATE_H_



#define UDR		  	  *((volatile u8 *)0x2C)
#define UCSRA 		  *((volatile u8 *)0x2B)
#define RXC				7
#define TXC				6
#define UDRE			5
#define PE				2

#define UCSRB		  *((volatile u8 *)0x2A)
#define RXEN     		4
#define TXEN      		3
#define UCSZ2      		2


#define UBRRL		  *((volatile u8 *)0x29)
#define UBRRH		  *((volatile u8 *)0x40)
#define UCSRC 	      *((volatile u8 *)0x40)

#define URSEL			7
#define UPM1			5
#define UPM0			4
#define USBS			3
#define UCSZ1			2
#define UCSZ0			1

#endif
