/**********************************/
/* Author :Ahmed Samir            */
/* SWC :TIMER0	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 17,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MTIMER0_PRIVATE_H_
#define _MTIMER0_PRIVATE_H_

// timner 0
#define TCCR0		*((volatile u8 *)0x53)

#define FOC0		7
#define WGM00		6
#define WGM01		3
#define COM01		5
#define COM00		4
#define CS02		2
#define CS01		1
#define CS00		0

#define TCNT0		*((volatile u8 *)0x52)
#define OCR0		*((volatile u8 *)0x5C)




// Timer 1

#define 	TCCR1A				*((volatile u8 *)0x4F)//control register for timer 1A

#define 	COM1A1			7
#define 	COM1A0			6
#define 	COM1B1			5
#define 	COM1B0			4
#define 	WGM11			1
#define 	WGM10			0

#define 	TCCR1B				*((volatile u8 *)0x4E)//control register for timer 1B

#define 	CS10			0
#define		CS11			1
#define 	CS12			2
#define 	WGM12			3
#define 	WGM13			4
#define 	ICES1			6

#define 	TCNT1				*((volatile u16 *)0x4C)
#define 	OCR1A				*((volatile u16 *)0x4A)
#define 	OCR1B				*((volatile u16 *)0x48)
#define 	ICR1				*((volatile u16 *)0x46)

// general for all timer

#define TIMSK		*((volatile u8 *)0x59)

#define TOIE0       0
#define OCIE0	    1
#define TICIE1		5


#define TIFR		*((volatile u8 *)0x58)

#define TOV0        0
#define OCF0	    1

#endif
