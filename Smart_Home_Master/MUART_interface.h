/**********************************/
/* Author :Ahmed Samir            */
/* SWC :MUART	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 24,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MUART_INTERFACE_H_
#define	_MUART_INTERFACE_H_

#define MUART_DATABITS_5				0
#define MUART_DATABITS_6				1
#define MUART_DATABITS_7				2
#define MUART_DATABITS_8				3
#define MUART_DATABITS_9				7

#define MUART_PARITY_NONE				0		
#define MUART_PARITY_EVEN				0x20	
#define MUART_PARITY_ODD				0x30

#define MUART_STOPBITS_1				0				
#define MUART_STOPBITS_2				0x08


#define MUART_INTERRUPT_RXC				7
#define MUART_INTERRUPT_TXC				6
#define MUART_INTERRUPT_UDR_EMPTY		5
	
	



STD_error_t MUART_stderrInit(u32 ARG_u32BudRate,u8 ARG_u8DataBits,u8 ARG_u8Parity,u8 ARG_u8StopBits);

void MUART_voidEnableTx(void);
void MUART_voidDisableTx(void);

void MUART_voidEnableRx(void);
void MUART_voidDisableRx(void);

void MUART_voidTxFlagPolling(void);
void MUART_voidRxFlagPolling(void);
void MUART_voidRUDREFlagPolling(void);

void MUART_voidSendChar(char ARG_charChar);
void MUART_voidSendString(char * ARG_charpString);


char MUART_charReceiveChar(void);
void MUART_voidReceiveStringUntil(char * ARG_charpString,char ARG_charTerminator);

STD_error_t MUART_stderrEnableInterrupt(u8 ARG_u8InterruptSource);
STD_error_t MUART_stderrDisableInterrupt(u8 ARG_u8InterruptSource);

STD_error_t MUART_stderrSetCallback(void(*ARG_pvoidfUserFunction)(void),u8 ARG_u8InterruptSource);


#endif
