/**********************************/
/* Author :Ahmed Samir            */
/* SWC :EEPREOM                   */
/* Layer :HAL 		              */
/* Version :1.0                   */
/* Date :September 3,2023         */
/* Last Edit :N/A                 */
/**********************************/
#include "util/delay.h"
#include"LSTD_types.h"
#include"LBIT_math.h"
#include"MTWI_interface.h"
#include"HNVM_private.h"
#include"HNVM_interface.h"
#include"HNVM_config.h"

STD_error_t HNVM_stderrInit(void)
{
	STD_error_t L_stderrState=E_OK;
	L_stderrState=MTWI_stderrInit(HNVM_BIT_RATE,HNVM_PRE_SCALER);
	MTWI_voidEnable();
	return L_stderrState;

}

// another approch is to make input block and location
void HNVM_voidWriteByte(u16 ARG_u16Address,u8 ARG_u8Data)
{
	u8 L_u8SlaveAddress;
	u8 L_u8Block;
	L_u8Block=(ARG_u16Address>>8);
	L_u8SlaveAddress=0b1010000|(L_u8Block);
	// send start condition ,clear the flag and wait for it to be set again to make sure the operation is done
	MTWI_voidSendStartCondition();
	//Clear the flag
	MTWI_voidClearFlag();
	//poll the flag
	MTWI_voidFlagPolling();
	// check the status code
	if(MTWI_STATUS_MASTER_START_CONDITION==MTIM_twistatusCheckStatus())
	{
		// the start condition is send sccuessfuly send the address of the slave
		// slave is 7 bit and the mask is to clear the first bit(write)
		MTWI_voidLoadTWDR(((((L_u8SlaveAddress<<1)&(0xFE))|(0))));
		//clear the flag
		MTWI_voidClearFlag();
		//poll the flag
		MTWI_voidFlagPolling();
		// check the status code
		if(MTWI_STATUS_MASTER_TX_SLA_W_ACK==MTIM_twistatusCheckStatus())
		{
			// loction of the choosen block
			MTWI_voidLoadTWDR((u8)ARG_u16Address);
			//clear the flag
			MTWI_voidClearFlag();
			//poll the flag
			MTWI_voidFlagPolling();
			// check the status code
			if(MTWI_STATUS_MASTER_TX_DATA_ACK==MTIM_twistatusCheckStatus())
			{
				MTWI_voidLoadTWDR(ARG_u8Data);
				//clear the flag
				MTWI_voidClearFlag();
				//poll the flag
				MTWI_voidFlagPolling();
				// check the status code
				if(MTWI_STATUS_MASTER_TX_DATA_ACK==MTIM_twistatusCheckStatus())
				{
					MTWI_voidClearFlag();
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
	else
	{

	}
	_delay_ms(10);

}
u8 HNVM_u8ReadByte(u16 ARG_u16Address)
{
	u8 L_u8Data;
	u8 L_u8SlaveAddress;
	u8 L_u8Block;
	L_u8Block=(ARG_u16Address>>8);
	L_u8SlaveAddress=0b1010000|(L_u8Block);
	// send start condition ,clear the flag and wait for it to be set again to make sure the operation is done
	MTWI_voidSendStartCondition();
	MTWI_voidClearFlag();
	MTWI_voidFlagPolling();
	// check the status code
	if(MTWI_STATUS_MASTER_START_CONDITION==MTIM_twistatusCheckStatus())
	{
		// the start condition is send sccuessfuly send the address of the slave
		// slave is 7 bit and the mask is to clear the first bit(write)
		MTWI_voidLoadTWDR(((((L_u8SlaveAddress<<1)&(0xFE))|(0))));
		MTWI_voidClearFlag();
		MTWI_voidFlagPolling();
		// check the status code
		if(MTWI_STATUS_MASTER_TX_SLA_W_ACK==MTIM_twistatusCheckStatus())
		{
			// Load the TWDR with the address of the chossen block
			MTWI_voidLoadTWDR((u8)ARG_u16Address);
			MTWI_voidClearFlag();
			MTWI_voidFlagPolling();
			// check the status code
			if(MTWI_STATUS_MASTER_TX_DATA_ACK==MTIM_twistatusCheckStatus())
			{
				// send repeated start to make read opertion
				MTWI_voidSendStartCondition();
				MTWI_voidClearFlag();
				MTWI_voidFlagPolling();
				// check the status code
				if(MTWI_STATUS_MASTER_RSTART_CONDITION==MTIM_twistatusCheckStatus())
				{
					MTWI_voidLoadTWDR(((((L_u8SlaveAddress<<1)&(0xFE))|(1))));
					MTWI_voidClearFlag();
					MTWI_voidFlagPolling();
					// check the status code
					if(MTWI_STATUS_MASTER_RX_SLA_R_ACK==MTIM_twistatusCheckStatus())
					{
						// wait until the data is recieved
						MTWI_voidClearFlag();
						MTWI_voidFlagPolling();
						if(MTWI_STATUS_MASTER_RX_DATA_NACK==MTIM_twistatusCheckStatus())
						{
							L_u8Data=MTWI_charReadTWDR();
							MTWI_voidClearFlag();
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
	_delay_ms(10);
	return L_u8Data;

}
