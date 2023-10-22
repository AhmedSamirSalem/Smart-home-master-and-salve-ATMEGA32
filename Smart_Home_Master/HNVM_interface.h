/**********************************/
/* Author :Ahmed Samir            */
/* SWC :EEPREOM                   */
/* Layer :HAL 		              */
/* Version :1.0                   */
/* Date :September 3,2023         */
/* Last Edit :N/A                 */
/**********************************/

#ifndef _HNVM_INTERFACE_H_
#define _HNVM_INTERFACE_H_

STD_error_t HNVM_stderrInit(void);

// another approch is to make input block and location
void HNVM_voidWriteByte(u16 ARG_u16Address,u8 ARG_u8Data);
u8 HNVM_u8ReadByte(u16 ARG_u16Address);




#endif