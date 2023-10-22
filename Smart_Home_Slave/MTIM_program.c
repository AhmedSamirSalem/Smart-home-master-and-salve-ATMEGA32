/**********************************/
/* Author :Ahmed Samir            */
/* SWC :TIMER0	               	  */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 17,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#include"LSTD_types.h"
#include"LBIT_math.h"

#include"MTIM_private.h"
#include"MTIM_interface.h"

void (*MTIMER0_pvoidfUserFunctionT0OVF)(void)=NULL;
void (*MTIMER0_pvoidfUserFunctionT0OCM)(void)=NULL;
void (*MTIMER1_pvoidfUserFunctionT1ICU)(void)=NULL;


u8 MTIM_u8Timer0Clock;
u8 MTIM_u8Timer1Clock;

volatile static u16 MTIM_u16Timer0OVFCount;
volatile static u8 MTIM_u8Timer0Preload;


STD_error_t MTIM_stderrInit(u8 ARG_u8TimerNo,u8 ARG_u8ClockSource,u8 ARG_u8Mode,u8 ARG_u8HWPinMode)
{
	STD_error_t L_stderrState=E_OK;
	if((ARG_u8TimerNo<=2)&&(ARG_u8ClockSource<=7)&&(ARG_u8Mode<=15)&&(ARG_u8HWPinMode<=3))
	{
		switch(ARG_u8TimerNo)
		{
		case MTIM_TIMER0:
		{
			switch(ARG_u8Mode)
			{
			case MTIM_MODE_NORMAL:
			{
				CLEAR_BIT(TCCR0,WGM00);
				CLEAR_BIT(TCCR0,WGM01);
				break;
			}
			case MTIM_MODE_CTC:
			{
				CLEAR_BIT(TCCR0,WGM00);
				SET_BIT(TCCR0,WGM01);
				break;
			}
			case MTIM_MODE_FASTPWM:
			{
				SET_BIT(TCCR0,WGM00);
				SET_BIT(TCCR0,WGM01);
				break;
			}
			case MTIM_MODE_PHASECORRECTPWM:
			{
				SET_BIT(TCCR0,WGM00);
				CLEAR_BIT(TCCR0,WGM01);
				break;
			}
			default:L_stderrState=E_NOK;break;
			}
			TCCR0=((TCCR0&0xCF)|(ARG_u8HWPinMode<<4));
			MTIM_u8Timer0Clock=ARG_u8ClockSource;
			break;
		}
		case MTIM_TIMER1:
		{
			switch(ARG_u8Mode)
			{
			case MTIM_MODE_NORMAL:
			{
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				break;
			}
			case MTIM_MODE_FASTPWMCTRLTOP:
			{
				CLEAR_BIT(TCCR1A,WGM10);
				SET_BIT(TCCR1A,WGM11);
				SET_BIT(TCCR1B,WGM12);
				SET_BIT(TCCR1B,WGM13);
				break;
			}
			default:L_stderrState=E_NOK;break;
			}
			if(ARG_u8HWPinMode==MTIM_HWPIN_DISCONNECTED)
			{
				CLEAR_BIT(TCCR1A,COM1A1);
				CLEAR_BIT(TCCR1A,COM1A0);
			}
			else if(ARG_u8HWPinMode==MTIM_HWPIN_NONINVERTING_PWM)
			{
				SET_BIT(TCCR1A,COM1A1);
				CLEAR_BIT(TCCR1A,COM1A0);
			}
			else
			{
				// add next options in the data sheet
			}
			MTIM_u8Timer1Clock=ARG_u8ClockSource;
			break;
		}
		case MTIM_TIMER2:
		{
			break;
		}
		default:L_stderrState=E_NOK;break;
		}
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}
void MTIM_voidForceOutputCompare(void)
{
	SET_BIT(TCCR0,FOC0);
}
STD_error_t MTIM_stderrEnableInterrupt(u8 ARG_u8InterruptSource)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_u8InterruptSource<=7)
	{
		SET_BIT(TIMSK,ARG_u8InterruptSource);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}
STD_error_t MTIM_stderrDisableInterrupt(u8 ARG_u8InterruptSource)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_u8InterruptSource<=7)
	{
		CLEAR_BIT(TIMSK,ARG_u8InterruptSource);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	return L_stderrState;
}
STD_error_t MTIM_stderrSetCallBack(u8 ARG_u8InterruptSource,void (*ARG_pvoidfUserFunction)(void))
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_pvoidfUserFunction!=NULL)
	{
		switch(ARG_u8InterruptSource)
		{
		case MTIM_INTERRUPT_T0_OVF:MTIMER0_pvoidfUserFunctionT0OVF=ARG_pvoidfUserFunction;break;
		case MTIM_INTERRUPT_T0_OCM:MTIMER0_pvoidfUserFunctionT0OCM=ARG_pvoidfUserFunction;break;
		case MTIM_INTERRUPT_T1_ICU:MTIMER1_pvoidfUserFunctionT1ICU=ARG_pvoidfUserFunction;break;
		default:L_stderrState=E_NOK;break;
		}
	}
	else
	{
		L_stderrState=E_NULL_POINTER;
	}	
	return L_stderrState;	
}
STD_error_t MTIM_stderrStartTimer(u8 ARG_u8TimerNo)
{
	STD_error_t L_stderrState=E_OK;
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		TCCR0=((TCCR0&0xF8)|MTIM_u8Timer0Clock);
		break;
	}
	case  MTIM_TIMER1:
	{

		TCCR1B=((TCCR1B&0xF8)|MTIM_u8Timer1Clock);
		break;
	}
	case  MTIM_TIMER2:
	{
		break;
	}
	default:L_stderrState=E_NOK;break;
	}
	return L_stderrState;
}
STD_error_t MTIM_stderrStopTimer(u8 ARG_u8TimerNo)
{
	STD_error_t L_stderrState=E_OK;
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		TCCR0=((TCCR0&0xF8)|MTIM_CS_NO_CLOCK);
		break;
	}
	case  MTIM_TIMER1:
	{
		TCCR1B=((TCCR1B&0xF8)|MTIM_CS_NO_CLOCK);
		break;
	}
	case  MTIM_TIMER2:
	{
		break;
	}
	default:L_stderrState=E_NOK;break;
	}
	return L_stderrState;
}
STD_error_t	MTIM_stderrSetOCR(u8 ARG_u8TimerNo,u16 ARG_u16OCRValue)
{
	STD_error_t L_stderrState=E_OK;
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		OCR0=ARG_u16OCRValue;
		break;
	}
	case  MTIM_TIMER1:
	{
		OCR1A=ARG_u16OCRValue;
		break;
	}
	case  MTIM_TIMER2:
	{
		break;
	}
	default:L_stderrState=E_NOK;break;
	}
	return L_stderrState;

}

STD_error_t	MTIM_stderrSetTimerValue(u8 ARG_u8TimerNo,u16 ARG_u16TimerValue)
{
	STD_error_t L_stderrState=E_OK;
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		TCNT0=ARG_u16TimerValue;
		break;
	}
	case  MTIM_TIMER1:
	{
		TCNT1=ARG_u16TimerValue;
		break;
	}
	case  MTIM_TIMER2:
	{
		break;
	}
	default:L_stderrState=E_NOK;break;
	}
	return L_stderrState;

}
STD_error_t MTIM_stderrTimerDelay(u8 ARG_u8TimerNo,u32 ARG_32msDelay)
{
	STD_error_t L_stderrState=E_OK;
	f32 L_f32TickTime,L_f32OVFTime;
	u16 L_u16PreScalar;
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		switch(MTIM_u8Timer0Clock)
		{
		case MTIM_CS_CLOCK_PRESCALAR_1:L_u16PreScalar=1;break;
		case MTIM_CS_CLOCK_PRESCALAR_8:L_u16PreScalar=8;break;
		case MTIM_CS_CLOCK_PRESCALAR_64:L_u16PreScalar=64;break;
		case MTIM_CS_CLOCK_PRESCALAR_256:L_u16PreScalar=256;break;
		case MTIM_CS_CLOCK_PRESCALAR_1024:L_u16PreScalar=1024;break;
		}
		L_f32TickTime=((f32)L_u16PreScalar/F_CPU);
		L_f32OVFTime=L_f32TickTime*256;
		MTIM_u16Timer0OVFCount=(((f32)ARG_32msDelay/1000)/L_f32OVFTime);
		//MTIM_u8Timer0Preload=256-((ARG_32msDelay/1000)%(u32)L_f32OVFTime);
		MTIM_u8Timer0Preload=256*(1-((((f32)ARG_32msDelay/1000)/L_f32OVFTime)-MTIM_u16Timer0OVFCount));

		TCNT0=MTIM_u8Timer0Preload;
		break;
	}
	case  MTIM_TIMER1:
	{
		break;
	}
	case  MTIM_TIMER2:
	{
		break;
	}
	default:L_stderrState=E_NOK;break;
	}
	return L_stderrState;
}
void __vector_11(void) __attribute__((signal));

void __vector_11(void)
{
	if(MTIMER0_pvoidfUserFunctionT0OVF!=NULL)
	{
		static volatile u16 L_u16OVFCounter=0;
		L_u16OVFCounter++;
		if(L_u16OVFCounter==(MTIM_u16Timer0OVFCount+1))
		{
			L_u16OVFCounter=0;
			TCNT0=MTIM_u8Timer0Preload;
			MTIMER0_pvoidfUserFunctionT0OVF();
		}
		else
		{
			//Do  Nothing;
		}

	}
	else
	{
		//report null pointer
	}
}
void __vector_10(void) __attribute__((signal));

void __vector_10(void)
{
	if(MTIMER0_pvoidfUserFunctionT0OCM!=NULL)
	{
		MTIMER0_pvoidfUserFunctionT0OCM();
	}
	else
	{
		//report null pointer
	}
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(MTIMER1_pvoidfUserFunctionT1ICU!=NULL)
	{
		MTIMER1_pvoidfUserFunctionT1ICU();
	}

}

void MTIM_voidBusyWaitDlay(u16 ARG_u16MsDelay)
{
	//loop counter
	u16 L_u16LoopCounter;
	// make the timer to work on ctc mode
	CLEAR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	// make the ocr0 register equal to 125 (so Time of the compare will be 1msec )
	MTIM_stderrSetOCR(MTIM_TIMER0,125);
	// make the pre scaler to 64 so the tick time is 8us
	TCCR0=((TCCR0&0xF8)|MTIM_CS_CLOCK_PRESCALAR_64);
	// the loop counter will count to the required delay each iteration is 1msec
	for(L_u16LoopCounter=0;L_u16LoopCounter<ARG_u16MsDelay;L_u16LoopCounter++)
	{
		while(!GET_BIT(TIFR,TOV0));
		SET_BIT(TIFR,TOV0);
	}
}

void MTIM_SetTimer1TopValue(u16 ARG_u8TopValue)
{
	ICR1=ARG_u8TopValue;
}


u16 MTIM_u16GetTimerValue(u8 ARG_u8TimerNo)
{
	u16 L_Return;
	switch(ARG_u8TimerNo)
	{
	case MTIM_TIMER0:
	{
		L_Return=TCNT0;
		break;
	}
	case  MTIM_TIMER1:
	{
		L_Return=TCNT1;
		break;
	}
	case  MTIM_TIMER2:
	{
		break;
	}
	default:break;//L_stderrState=E_NOK;break;
	}
	return L_Return;
}


//icu  function

void ICU_voidSetEdge(u8 Copy_u8Edge)
{
	if(Copy_u8Edge==ICU_RISINGEDGE)
	{
		SET_BIT(TCCR1B,ICES1);
	}
	else if(Copy_u8Edge==ICU_FALLINGEDGE)
	{
		CLEAR_BIT(TCCR1B,ICES1);
	}
}
void ICU_voidEnableint(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void ICU_voidDisableint(void)
{
	CLEAR_BIT(TIMSK,TICIE1);
}
u16	ICU_u16ReadICU(void)
{
	return	ICR1;
}



