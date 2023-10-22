/**********************************/
/* Author :Ahmed Samir            */
/* SWC :MTWI	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 29,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#include"LSTD_types.h"
#include"LBIT_math.h"
#include"MTWI_private.h"
#include"MTWI_interface.h"


static void (*MTWI_pvoidfUserfunction)(void);
STD_error_t MTWI_stderrInit(u32 ARG_u32DataRate,u8 ARG_u8PreScalar)
{
	STD_error_t L_stderrState=E_OK;
	switch(ARG_u8PreScalar)
	{
	case 0:TWBR=((F_CPU/ARG_u32DataRate)-16)/(2);break;
	case 1:TWBR=((F_CPU/ARG_u32DataRate)-16)/(8);break;
	case 2:TWBR=((F_CPU/ARG_u32DataRate)-16)/(32);break;
	case 3:TWBR=((F_CPU/ARG_u32DataRate)-16)/(128);break;
	default:L_stderrState=E_NOK;break;
	}
	if((ARG_u8PreScalar<=3))
	{
		TWSR=(TWSR&0xFC)|(ARG_u8PreScalar);		
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}


void MTWI_voidEnable(void)
{
	SET_BIT(TWCR,TWEN);
}
void MTWI_voidDisable(void)
{
	CLEAR_BIT(TWCR,TWEN);
}

void MTWI_EnableInterrupt(void)
{
	SET_BIT(TWCR,TWIE);
}
void MTWI_DisableInterrupt(void)
{
	CLEAR_BIT(TWCR,TWIE);
}

STD_error_t MTWI_stderrSetCallback(void(*ARG_pvoidfUserFunction)(void))
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_pvoidfUserFunction!=NULL)
	{
		MTWI_pvoidfUserfunction=ARG_pvoidfUserFunction;
	}
	else
	{
		L_stderrState=E_NULL_POINTER;
	}
	return L_stderrState;
}

void MTWI_voidSendStartCondition(void)
{
	//TWCR =(TWCR&0x5f)| (1<<TWINT)|(1<<TWSTA);
	SET_BIT(TWCR,TWSTA);
}
void MTWI_voidSendStopCondition(void)
{
	//TWCR = (TWCR&0x6f)| (1<<TWINT)|(1<<TWSTO);
	SET_BIT(TWCR,TWSTO);
}

void MTWI_voidEnableACK(void)
{
	SET_BIT(TWCR,TWEA);
}
void MTWI_voidDisableACK(void)
{
	CLEAR_BIT(TWCR,TWEA);
}


void MTWI_voidEnableGeneralCall(void)
{
	SET_BIT(TWAR,TWGCE);
}
void MTWI_voidDisableGeneralCall(void)
{
	CLEAR_BIT(TWAR,TWGCE);
}

void MTWI_voidSetSalveAddress(u8 ARG_u8SlaveAddress)
{
	// i make the shift to ensure that the general call bit is not affected
	TWAR=(TWAR&0x01)|(ARG_u8SlaveAddress<<1);
}

MTWI_status MTIM_twistatusCheckStatus(void)
{
	return (TWSR&TWSR_MASK);
}

void MTWI_voidFlagPolling(void)
{
	while(!GET_BIT(TWCR,TWINT));
}
void MTWI_voidClearFlag(void)
{
	TWCR=(TWCR&0x4F)|(1<< TWINT)|(1<<TWEN);
}
void MTWI_voidLoadTWDR(u8 ARG_u8Data)
{
	TWDR=ARG_u8Data;
}
char MTWI_charReadTWDR(void)
{
	return TWDR;
}


// will send the entire frame(start+sla r/w+data+stop);
// will be used in application
void MTWI_voidSendChar(u8 ARG_u8SlaveAddress,char ARG_charChar)
{
	// send start condition ,clear the flag and wait for it to be set again to make sure the operation is done
	MTWI_voidSendStartCondition();
	MTWI_voidClearFlag();
	//poll the flag
	MTWI_voidFlagPolling();
	// check the status code
	if(MTWI_STATUS_MASTER_START_CONDITION==MTIM_twistatusCheckStatus())
	{
		// the start condition is send sccuessfuly send the address of the slave
		// slave is 7 bit and the mask is to clear the first bit(write)
		MTWI_voidLoadTWDR(((((ARG_u8SlaveAddress<<1)&(0xFE))|(0))));
		//clear the flag
		MTWI_voidClearFlag();
		//poll the flag
		MTWI_voidFlagPolling();
		// check the status code
		if(MTWI_STATUS_MASTER_TX_SLA_W_ACK==MTIM_twistatusCheckStatus())
		{
			// load the data in the register
			MTWI_voidLoadTWDR(ARG_charChar);
			//clear the flag
			MTWI_voidClearFlag();
			//poll the flag
			MTWI_voidFlagPolling();
			// check the status code
			if(MTWI_STATUS_MASTER_TX_DATA_ACK==MTIM_twistatusCheckStatus())
			{
				MTWI_voidSendStopCondition();
			}
			else
			{

			}	
		}
		else
		{

		}

	}
	else
	{

	}
}
void MTWI_voidSendMultipleChar(u8 ARG_u8SlaveAddress,const char *  ARG_ccharpString)
{
	u16 L_u16StringCounter=0;
	// send start condition ,clear the flag and wait for it to be set again to make sure the operation is done
	MTWI_voidSendStartCondition();
	MTWI_voidClearFlag();
	MTWI_voidFlagPolling();
	// check the status code
	if(MTWI_STATUS_MASTER_START_CONDITION==MTIM_twistatusCheckStatus())
	{
		// the start condition is send sccuessfuly send the address of the slave
		// slave is 7 bit and the mask is to clear the first bit(write)
		MTWI_voidLoadTWDR(((((ARG_u8SlaveAddress<<1)&(0xFE))|(0))));
		//clear the flag
		MTWI_voidClearFlag();
		//poll the flag
		MTWI_voidFlagPolling();
		// check the status code
		if(MTWI_STATUS_MASTER_TX_SLA_W_ACK==MTIM_twistatusCheckStatus())
		{
			do
			{
				// load the data in the register
				MTWI_voidLoadTWDR(ARG_ccharpString[L_u16StringCounter]);
				//clear the flag
				MTWI_voidClearFlag();
				//poll the flag
				MTWI_voidFlagPolling();
				// check the status code
				L_u16StringCounter++;
			}while(ARG_ccharpString[L_u16StringCounter]!='\0' &&(MTWI_STATUS_MASTER_TX_DATA_ACK==MTIM_twistatusCheckStatus()));
		}
		else
		{

		}
	}
	else
	{

	}
}

char MTWI_charSlaveReceive(void)
{
	char L_charReturn;
	//clear the flag
	MTWI_voidClearFlag();
	//poll the flag
	MTWI_voidFlagPolling();
	if(MTWI_STATUS_SLAVE_RX_SLA_W_ACK==MTIM_twistatusCheckStatus())
	{
		//clear the flag
		MTWI_voidClearFlag();
		//poll the flag
		MTWI_voidFlagPolling();
		if(MTWI_STATUS_SLAVE_RX_SLA_W_DATA_ACK==MTIM_twistatusCheckStatus())
		{
			L_charReturn=MTWI_charReadTWDR();
			//clear the flag
			MTWI_voidClearFlag();
			//poll the flag
			MTWI_voidFlagPolling();
			if(MTWI_STATUS_SLAVE_RX_STOP_RSTART==MTIM_twistatusCheckStatus())
			{
				MTWI_voidClearFlag();
			}
		}
		else
		{

		}
	}
	return L_charReturn;
}


