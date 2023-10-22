/**********************************/
/* Author :Ahmed Samir            */
/* SWC :TIMER0	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 17,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MTIM0_INTERFACE_H_
#define _MTIM0_INTERFACE_H_

#define MTIM_TIMER0							0
#define MTIM_TIMER1							1
#define MTIM_TIMER2							2

#define MTIM_MODE_NORMAL					0
#define MTIM_MODE_CTC						1
#define MTIM_MODE_FASTPWM					2
#define MTIM_MODE_PHASECORRECTPWM			3
#define MTIM_MODE_FASTPWMCTRLTOP			14

#define MTIM_CS_NO_CLOCK					0
#define MTIM_CS_CLOCK_PRESCALAR_1			1
#define MTIM_CS_CLOCK_PRESCALAR_8			2
#define MTIM_CS_CLOCK_PRESCALAR_64			3	
#define MTIM_CS_CLOCK_PRESCALAR_256			4
#define MTIM_CS_CLOCK_PRESCALAR_1024		5
#define MTIM_CS_T0_FALLING					6
#define MTIM_CS_T0_RISING					7

#define MTIM_HWPIN_DISCONNECTED				0
#define MTIM_HWPIN_TOGGLE					1
#define MTIM_HWPIN_CLEAR					2
#define MTIM_HWPIN_SET						3

#define MTIM_HWPIN_NONINVERTING_PWM			2
#define MTIM_HWPIN_INVERTING_PWM			3


#define MTIM_INTERRUPT_T0_OVF				0
#define MTIM_INTERRUPT_T0_OCM				1
#define	MTIM_INTERRUPT_T1_ICU				5


#define ICU_RISINGEDGE	1
#define ICU_FALLINGEDGE	2

#ifndef F_CPU
#define F_CPU 80000000UL
#warning "the F_CPU is not defined and assumed to be 8MHZ"
#endif

STD_error_t MTIM_stderrInit(u8 ARG_u8TimerNo,u8 ARG_u8ClockSource,u8 ARG_u8Mode,u8 ARG_u8HWPinMode);
void MTIM_voidForceOutputCompare(void);
STD_error_t MTIM_stderrEnableInterrupt(u8 ARG_u8InterruptSource);
STD_error_t MTIM_stderrDisableInterrupt(u8 ARG_u8InterruptSource);
STD_error_t MTIM_stderrSetCallBack(u8 ARG_u8InterruptSource,void (*ARG_pvoidfUserFunction)(void));
STD_error_t MTIM_stderrStartTimer(u8 ARG_u8TimerNo);
STD_error_t MTIM_stderrStopTimer(u8 ARG_u8TimerNo);
STD_error_t	MTIM_stderrSetOCR(u8 ARG_u8TimerNo,u16 ARG_u16OCRValue);
STD_error_t MTIM_stderrTimerDelay(u8 ARG_u8TimerNo,u32 ARG_32msDelay);

void MTIM_SetTimer1TopValue(u16 ARG_u8TopValue);

void MTIM_voidBusyWaitDlay(u16 ARG_u16MsDelay);
STD_error_t	MTIM_stderrSetTimerValue(u8 ARG_u8TimerNo,u16 ARG_u16TimerValue);

u16 MTIM_u16GetTimerValue(u8 ARG_u8TimerNo);


void ICU_voidSetEdge(u8 Copy_u8Edge);
void ICU_voidEnableint(void);
void ICU_voidDisableint(void);
u16	ICU_u16ReadICU(void);

#endif
