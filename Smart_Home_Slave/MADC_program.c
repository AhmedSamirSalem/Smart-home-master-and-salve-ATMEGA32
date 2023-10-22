/**********************************/
/* Author :Ahmed Samir            */
/* SWC :ADC	               	      */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 14,2023           */
/* Last Edit :N/A      			  */
/**********************************/
#include"LSTD_types.h"
#include"LBIT_math.h"

#include"MADC_private.h"
#include"MADC_config.h"
#include"MADC_interface.h"

static u8 MADC_State=MADC_NOTBUSY;
static void (*MADC_pvoidfIntFunc)(void)=NULL;
STD_error_t MADC_stderrInit(u8 ARG_u8VrefSelect,u8 ARG_uPreScalerSelect)
{
	STD_error_t L_stderrErrorState=E_OK;
	if(ARG_uPreScalerSelect<=MADC_PRESCALER_128 &&(ARG_u8VrefSelect<=MADC_VREF_AVCC || MADC_VREF_2_56V==ARG_u8VrefSelect))
	{
		ADMUX=((ADMUX&ADMUX_VREF_MASK)|(ARG_u8VrefSelect<<REFS0));
	#if LEFT_ADJUST_ENABLE==1
		SET_BIT(ADMUX,ADLAR);
	#elif LEFT_ADJUST_ENABLE==2
		CLEAR_BIT(ADMUX,ADLAR);
	#else
		#error"Wrong ADLAR choice"
	#endif
		ADCSRA=((ADCSRA&ADCSRA_PRESCALER_MASK)|ARG_uPreScalerSelect);
	}
	else
	{
		L_stderrErrorState=E_NOK;
	}
	return L_stderrErrorState;	
}

STD_error_t MADC_stderrStartConversion(u8 ARG_u8Channel)
{
	STD_error_t L_stderrErrorState=E_OK;
	if(ARG_u8Channel<=MADC_CHANNEL_ADC7)
	{
		ADMUX=((ADMUX&ADMUX_CHANNEL_MASK)|ARG_u8Channel);
		SET_BIT(ADCSRA,ADSC);
	}
	else
	{
		L_stderrErrorState=E_NOK;
	}
	return L_stderrErrorState;
}
void MADC_voidAdcEnable(void)
{
	SET_BIT(ADCSRA,ADEN);
}
void MADC_voidAdcDisable(void)
{
	CLEAR_BIT(ADCSRA,ADEN);
}
void MADC_voidWaitFlag(void)
{
	while(!GET_BIT(ADCSRA,ADIF));
}
void MADC_voidClearFlag(void)
{
	SET_BIT(ADCSRA,ADIF);
}

void MADC_voidAdcEnableInt(void)
{
	SET_BIT(ADCSRA,ADIE);
}
void MADC_voidAdcDisableInt(void)
{
	CLEAR_BIT(ADCSRA,ADIE);
}
STD_error_t MADC_stderrRead(u16 * ARG_u16pReading,u8 ARG_u8Channel)
{
	STD_error_t L_stderrErrorState=E_OK;
	if(ARG_u16pReading!=NULL)
	{
		L_stderrErrorState=MADC_stderrStartConversion(ARG_u8Channel);
		MADC_voidWaitFlag();
		MADC_voidClearFlag();
		#if LEFT_ADJUST_ENABLE==1
		*ARG_u16pReading=ADCH;
		#elif LEFT_ADJUST_ENABLE==2
		*ARG_u16pReading=(u16)ADCL;
		#endif
	}
	else
	{
		L_stderrErrorState=E_NULL_POINTER;
	}
	return L_stderrErrorState;
}


STD_error_t MADC_stderrReadAsynch(u8 ARG_u8Channel)
{
	STD_error_t L_stderrErrorState=E_OK;
	if(MADC_State==MADC_NOTBUSY)
	{
		MADC_State=MADC_BUSY;
		MADC_voidAdcEnableInt();
		L_stderrErrorState=MADC_stderrStartConversion(ARG_u8Channel);
	}
	else
	{
		L_stderrErrorState=E_NOK;
	}
	return L_stderrErrorState;
}
u16 MADC_u16Reading(void)
{
	#if LEFT_ADJUST_ENABLE==1
	return ADCH;
	#elif LEFT_ADJUST_ENABLE==2
	return (ADCL);
	#endif
}

STD_error_t MADC_stderrSetCallBack(void (*ARG_pvoidfIsrFunc)(void))
{
	STD_error_t L_stderrErrorState=E_OK;
	if(ARG_pvoidfIsrFunc!=NULL)
	{
		MADC_pvoidfIntFunc=ARG_pvoidfIsrFunc;
	}
	else
	{
		L_stderrErrorState=E_NULL_POINTER;
	}
	return L_stderrErrorState;
}
void __vector_16(void) __attribute__((signal));

void __vector_16(void)
{
	if(MADC_pvoidfIntFunc!=NULL)
	{
		MADC_State=MADC_NOTBUSY;
		MADC_pvoidfIntFunc();
	}
}
// my functions 
void MADC_voidInit(void)
{
	
	// Vref
	#if MADC_VREF_AREF==MADC_VREF_CHOICE
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);	
	#elif MADC_VREF_AVCC==MADC_VREF_CHOICE
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
	#elif MADC_VREF_2_56V==MADC_VREF_CHOICE
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	#else 
		#error"Wrong Vref choice"
	#endif
	//Pre scaler
	#if MADC_PRESCALER_2==MADC_PRESCALER_CHOICE
		SET_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);		
	#elif MADC_PRESCALER_4==MADC_PRESCALER_CHOICE
		CLEAR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);
	#elif MADC_PRESCALER_8==MADC_PRESCALER_CHOICE
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLEAR_BIT(ADCSRA,ADPS2);
	#elif MADC_PRESCALER_16==MADC_PRESCALER_CHOICE
		CLEAR_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif MADC_PRESCALER_32==MADC_PRESCALER_CHOICE
		SET_BIT(ADCSRA,ADPS0);
		CLEAR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif MADC_PRESCALER_64==MADC_PRESCALER_CHOICE
		CLEAR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
	#elif MADC_PRESCALER_128==MADC_PRESCALER_CHOICE
		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);			
	#else 
		#error"Wrong pre scaler choice"
	#endif
	
	#if LEFT_ADJUST_ENABLE==1
		SET_BIT(ADMUX,ADLAR);
	#elif LEFT_ADJUST_ENABLE==2
		CLEAR_BIT(ADMUX,ADLAR);
	#else 
		#error"Wrong ADLAR choice"
	#endif
	
}
u8 MADC_u8StartConversionSynch(u8 ARG_u8Channel)
{
	// enable ADC 
	SET_BIT(ADCSRA,ADEN);
	// set channel;
	ADMUX&=ADMUX_CHANNEL_MASK;
	ADMUX|=ARG_u8Channel;
	// Start conversion
	SET_BIT(ADCSRA,ADSC);
	// wait for the flag to be set
	while(!GET_BIT(ADCSRA,ADIF));
	// clear the flag
	SET_BIT(ADCSRA,ADIF);
	// return the result
	return ADCH;
	
}
