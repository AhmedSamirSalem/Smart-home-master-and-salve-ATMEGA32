/**********************************/
/* Author :Ahmed Samir            */
/* SWC :MUART	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 24,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#include"LSTD_types.h"
#include"LBIT_math.h"
#include"MUART_private.h"
#include"MUART_interface.h"

static void (*MUART_pvoidfUserFunctionRxC)(void)=NULL;
static void (*MUART_pvoidfUserFunctionTxC)(void)=NULL;
static void (*MUART_pvoidfUserFunctionUDREmpty)(void)=NULL;


STD_error_t MUART_stderrInit(u32 ARG_u32BudRate,u8 ARG_u8DataBits,u8 ARG_u8Parity,u8 ARG_u8StopBits)
{
	STD_error_t L_stderrState=E_OK;
	if((ARG_u8DataBits<=3 ||7== ARG_u8DataBits)&&((0x20==ARG_u8Parity)||(0x20==ARG_u8Parity)||(0x30==ARG_u8Parity))&&
		((0==ARG_u8StopBits)||(0x08==ARG_u8StopBits)))
	{
		u16 UBBR;
		UBBR=((F_CPU/(16*ARG_u32BudRate))-1);
		UBRRL=(u8)UBBR;
		UBRRH=(u8)((UBBR>>8)&0X0F);
		UCSRB=(UCSRB&0xFC)|(ARG_u8DataBits&0x04);
		UCSRC=(1<<URSEL)|(UCSRC&0XC1)|((ARG_u8DataBits&0X03)<<1)|(ARG_u8Parity)|(ARG_u8StopBits);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}

void MUART_voidEnableTx(void)
{
	SET_BIT(UCSRB,TXEN);
}
void MUART_voidDisableTx(void)
{
	CLEAR_BIT(UCSRB,TXEN);
}

void MUART_voidEnableRx(void)
{
	SET_BIT(UCSRB,RXEN);
}
void MUART_voidDisableRx(void)
{
	CLEAR_BIT(UCSRB,RXEN);
}

void MUART_voidTxFlagPolling(void)
{
	while(0==GET_BIT(UCSRA,TXC));
}
void MUART_voidRxFlagPolling(void)
{
	while(0==GET_BIT(UCSRA,RXC));
}
void MUART_voidRUDREFlagPolling(void)
{
	while(0==GET_BIT(UCSRA,UDRE));
}

void MUART_voidSendChar(char ARG_charChar)
{
	MUART_voidRUDREFlagPolling();
	UDR=ARG_charChar;
}
void MUART_voidSendString(char * ARG_charpString)
{
	u32 L_u32Counter=0;
	while(ARG_charpString[L_u32Counter]!='\0')
	{
		L_u32Counter++;
		MUART_voidSendChar(ARG_charpString[L_u32Counter]);	
	}
}


char MUART_charReceiveChar(void)
{
	MUART_voidRxFlagPolling();
	return	UDR;
}
void MUART_voidReceiveStringUntil(char * ARG_charpString,char ARG_charTerminator)
{
	u32 L_u32Counter=0;
	ARG_charpString[L_u32Counter]=MUART_charReceiveChar();
	while(ARG_charpString[L_u32Counter]!=ARG_charTerminator)
	{
		L_u32Counter++;
		ARG_charpString[L_u32Counter]=MUART_charReceiveChar();
	}
	ARG_charpString[L_u32Counter]='\0';
}

STD_error_t MUART_stderrEnableInterrupt(u8 ARG_u8InterruptSource)
{
	STD_error_t L_stderrState=E_OK;
	if((ARG_u8InterruptSource>=5)&&(ARG_u8InterruptSource<=7))
	{
		SET_BIT(UCSRB,ARG_u8InterruptSource);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}
STD_error_t MUART_stderrDisableInterrupt(u8 ARG_u8InterruptSource)
{
	STD_error_t L_stderrState=E_OK;
	if((ARG_u8InterruptSource>=5)&&(ARG_u8InterruptSource<=7))
	{
	CLEAR_BIT(UCSRB,ARG_u8InterruptSource);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}

STD_error_t MUART_stderrSetCallback(void(*ARG_pvoidfUserFunction)(void),u8 ARG_u8InterruptSource)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_pvoidfUserFunction!=NULL)
	{
		switch(ARG_u8InterruptSource)
		{
			case MUART_INTERRUPT_RXC:MUART_pvoidfUserFunctionRxC=ARG_pvoidfUserFunction;break;
			case MUART_INTERRUPT_TXC:MUART_pvoidfUserFunctionTxC=ARG_pvoidfUserFunction;break;
			case MUART_INTERRUPT_UDR_EMPTY:MUART_pvoidfUserFunctionUDREmpty=ARG_pvoidfUserFunction;break;
			default: L_stderrState=E_NOK;
		}
	}
	else
	{
		L_stderrState=E_NULL_POINTER;
	}
	return L_stderrState;
}
void __vector_13(void)  __attribute__((signal));
void __vector_13(void)
{
	if(MUART_pvoidfUserFunctionRxC!=NULL)
	{
		MUART_pvoidfUserFunctionRxC();
	}
}
void __vector_14(void)  __attribute__((signal));
void __vector_14(void)
{
	if(MUART_pvoidfUserFunctionUDREmpty!=NULL)
	{
		MUART_pvoidfUserFunctionUDREmpty();
	}
}
void __vector_15(void)  __attribute__((signal));
void __vector_15(void)
{
	if(MUART_pvoidfUserFunctionTxC!=NULL)
	{
		MUART_pvoidfUserFunctionTxC();
	}
}
