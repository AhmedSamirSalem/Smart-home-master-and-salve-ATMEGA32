/**********************************/
/* Author :Ahmed Samir            */
/* SWC :TWI	      	         	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 29,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MTWI_INTERFACE_H_
#define	_MTWI_INTERFACE_H_
#include "LSTD_types.h"
typedef enum
{
	MTWI_STATUS_MASTER_START_CONDITION             = 0x08,
	MTWI_STATUS_MASTER_RSTART_CONDITION            = 0x10,
	MTWI_STATUS_MASTER_TX_SLA_W_ACK                = 0x18,
	MTWI_STATUS_MASTER_TX_SLA_W_NACK               = 0x20,
	MTWI_STATUS_MASTER_TX_DATA_ACK                 = 0x28,
	MTWI_STATUS_MASTER_TX_DATA_NACK                = 0x30,
	MTWI_STATUS_MASTER_TX_SLA_W_OR_DATA_LOST_ARB   = 0x38,
	MTWI_STATUS_MASTER_RX_SLA_R_OR_NACK_LOST_ARB   = 0x38,
	MTWI_STATUS_MASTER_RX_SLA_R_ACK                = 0x40,
	MTWI_STATUS_MASTER_RX_SLA_R_NACK               = 0x48,
	MTWI_STATUS_MASTER_RX_DATA_ACK                 = 0x50,
	MTWI_STATUS_MASTER_RX_DATA_NACK                = 0x58,
	MTWI_STATUS_SLAVE_RX_SLA_W_ACK                 = 0x60,
	MTWI_STATUS_SLAVE_RX_SLA_W_ACK_LOST_ARB        = 0x68,
	MTWI_STATUS_SLAVE_RX_GENERAL_CALL_ACK          = 0x70,
	MTWI_STATUS_SLAVE_RX_GENERAL_CALL_ACK_LOST_ARB = 0x78,
	MTWI_STATUS_SLAVE_RX_SLA_W_DATA_ACK            = 0x80,
	MTWI_STATUS_SLAVE_RX_SLA_W_DATA_NACK           = 0x88,
	MTWI_STATUS_SLAVE_RX_GENERAL_CALL_DATA_ACK     = 0x90,
	MTWI_STATUS_SLAVE_RX_GENERAL_CALL_DATA_NACK    = 0x98,
	MTWI_STATUS_SLAVE_RX_STOP_RSTART               = 0xA0,
	MTWI_STATUS_SLAVE_TX_SLA_R_ACK                 = 0xA8,
	MTWI_STATUS_SLAVE_TX_SLA_R_ACK_LOST_ARB        = 0xB0,
	MTWI_STATUS_SLAVE_TX_DATA_ACK                  = 0xB8,
	MTWI_STATUS_SLAVE_TX_DATA_NACK                 = 0xC0,
	MTWI_STATUS_SLAVE_TX_LAST_DATA_ACK             = 0xC8,
	MTWI_STATUS_NO_RELEVANT_STATE                  = 0xF8,
	MTWI_STATUS_BUS_ERROR_ILLEGAL_START_STOP       = 0x00
}MTWI_status;

#define MTWI_PRESCALAR_1	0
#define MTWI_PRESCALAR_4	1
#define MTWI_PRESCALAR_16	2
#define MTWI_PRESCALAR_64	3

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_stderrInit
*
*[Description]: This function is responsible for init the freq of scl (master) 
*
*[Arguments]:
*
*[in]:  u8 ARG_u32DataRate:This Argument indicates the the freq 
*       u8 ARG_u8PreScalar  :   This Argument indicates the required PreScalar
*
*[out]: N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK
--------------------------------------------------------------------------------------------------------------------*/
STD_error_t MTWI_stderrInit(u32 ARG_u32DataRate,u8 ARG_u8PreScalar);


/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidEnable
*
*[Description]: This function is responsible for enabling the twi (master,slave) 
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidEnable(void);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidDisable
*
*[Description]: This function is responsible for Disabling the twi (master,slave) 
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidDisable(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_EnableInterrupt
*
*[Description]: This function is responsible for Enabling Interrupt the twi (master,slave) 
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_EnableInterrupt(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_DisableInterrupt
*
*[Description]: This function is responsible for Disabling Interrupt the twi (master,slave) 
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_DisableInterrupt(void);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_DisableInterrupt
*
*[Description]: This function is responsible for Disabling Interrupt the twi (master,slave) 
*
*[Arguments]:
*
*[in]:  void(*ARG_pvoidfUserFunction)(void):This Argument indicates pointer to function that will be called when interrupt happens
*
*[out]: N/A
*
*[Returns]: STD_error_t :Function returns Error code E_OK or E_NOK or E_NULL_POINTER
--------------------------------------------------------------------------------------------------------------------*/
STD_error_t MTWI_stderrSetCallback(void(*ARG_pvoidfUserFunction)(void));

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidSendStartCondition
*
*[Description]: This function is responsible for sending Start Condition  (master)
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidSendStartCondition(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidSendStopCondition
*
*[Description]: This function is responsible for sending Stop Condition  (master)
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidSendStopCondition(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidEnableACK
*
*[Description]: This function is responsible for enabling ACK (master->data recieve, Slave->when recieve or addresed)
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidEnableACK(void);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidDisableACK
*
*[Description]: This function is responsible for Disabling ACK (master->data recieve, Slave->when recieve or addresed)
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidDisableACK(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidEnableGeneralCall
*
*[Description]: This function is responsible for enabling General Call 
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidEnableGeneralCall(void);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidDisableGeneralCall
*
*[Description]: This function is responsible for Disabling General Call 
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidDisableGeneralCall(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidSetSalveAddress
*
*[Description]: This function is responsible for Setting the slave addres that it will be addresed by  
*
*[Arguments]:
*
*[in]:  u8 ARG_u8SlaveAddress:This Argument indicates the slave addres
*
*[out]: N/A
*
*[Returns]: N/A 
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidSetSalveAddress(u8 ARG_u8SlaveAddress);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTIM_twistatusCheckStatus
*
*[Description]: This function is responsible for returning the status of the bus   
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: MTWI_status
--------------------------------------------------------------------------------------------------------------------*/
MTWI_status MTIM_twistatusCheckStatus(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidFlagPolling
*
*[Description]: This function is responsible for polling the flag to make sure that the opertion is done succesfully   
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidFlagPolling(void);

/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidClearFlag
*
*[Description]: This function is responsible for Clearing the flag to make sure that the opertion is started succesfully  (must be done before any opertion )
*				note:Not cleared by hardware
*
*[Arguments]:
*
*[in]:  N/A
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidClearFlag(void);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidLoadTWDR
*
*[Description]: This function is responsible for Loading data to bus(addres+r/W or data to be sent) 
*
*[Arguments]:
*
*[in]: u8 ARG_u8Data:This Argument indicates the data will be sent 
*
*[out]: N/A
*
*[Returns]: N/A
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidLoadTWDR(u8 ARG_u8Data);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_charReadTWDR
*
*[Description]: This function is responsible for Loading data to bus(addres+r/W or data to be sent) 
*
*[Arguments]:
*
*[in]: N/A
*
*[out]: N/A
*
*[Returns]: Char:data recieved on the bus(may be addres or data)
--------------------------------------------------------------------------------------------------------------------*/
char MTWI_charReadTWDR(void);


// will send the entire frame(start+sla r/w+data+stop);
// will be used in application
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_voidSendChar
*
*[Description]: This function is responsible for all the steps to send data as master on in the bus
*				steps:1-Send Start Condition,Clear flag,PollFLag,Check Status
*					  2-if the status is ok:load Slave addres+(r/W),,Clear flag,PollFLag,Check Status
*					  3-if the status is ok:load Data,Clear flag,PollFLag,Check Status
*					  4-if the status is ok:Send STOP,Repeated Start		
*
*[Arguments]:
* 
*[in]:		u8 ARG_u8SlaveAddress:This Argument indicates the salve addres to be communicated with
*			char ARG_charChar:This Argument indicates the data will be transmitted to the slave
*
*[out]: N/A
*
*[Returns]:N/A
--------------------------------------------------------------------------------------------------------------------*/
void MTWI_voidSendChar(u8 ARG_u8SlaveAddress,char ARG_charChar);

void MTWI_voidSendMultipleChar(u8 ARG_u8SlaveAddress,const char *  ARG_ccharpString);
/*--------------------------------------------------------------------------------------------------------------------
*[Function Name]: MTWI_charSlaveReceive
*
*[Description]: This function is responsible for all the steps to recieve data as Slave on in the bus
*				steps:1-Clear flag,PollFLag, waiting to listen your address ,Check Status
*					  2-if the status is ok:-Clear flag,PollFLag, waiting to data,Check Status
*					  3-if the status is ok:Get Data,Clear flag,PollFLag,waiting to Stop condition ,Check Status
*					  4-if the status is ok:Clear flag(communication is end) or in case of repeated start continue sending data		
*
*[Arguments]:
* 
*[in]:		u8 ARG_u8SlaveAddress:This Argument indicates the salve addres to be communicated with
*			char ARG_charChar:This Argument indicates the data will be transmitted to the slave
*
*[out]: N/A
*
*[Returns]:N/A
--------------------------------------------------------------------------------------------------------------------*/
char MTWI_charSlaveReceive(void);

#endif
