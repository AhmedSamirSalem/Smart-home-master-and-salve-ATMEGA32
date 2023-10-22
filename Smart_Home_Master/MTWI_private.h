/**********************************/
/* Author :Ahmed Samir            */
/* SWC :TWI		               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 29,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MTWI_PRIVATE_H_
#define	_MTWI_PRIVATE_H_



#define TWCR			*((volatile u8*)0x56)

#define TWINT			7
#define TWEA			6
#define TWSTA			5
#define TWSTO			4
#define TWWC			3
#define TWEN			2
#define TWIE			0


#define TWDR			*((volatile u8*)0x23)

#define TWAR			*((volatile u8*)0x22)
#define TWGCE			0

#define TWSR			*((volatile u8*)0x21)
#define TWPS0			0
#define TWPS1			1

#define TWBR			*((volatile u8*)0x20)

#define TWSR_MASK 0xF8

#endif