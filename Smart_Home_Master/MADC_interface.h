/**********************************/
/* Author :Ahmed Samir            */
/* SWC :ADC	               	      */
/* Layer :MCAL 		              */
/* Version :1.0                   */
/* Date :August 14,2023           */
/* Last Edit :N/A      			  */
/**********************************/

#ifndef _MADC_INTERFACE_H_
#define _MADC_INTERFACE_H_

#define MADC_VREF_AREF			0
#define MADC_VREF_AVCC			1
#define MADC_VREF_2_56V			3
#define ADMUX_VREF_MASK 		0x3F
#define MADC_VREF_CHOICE		MADC_VREF_AVCC		//(MADC_VREF_AREF,MADC_VREF_AVCC,MADC_VREF_2_56V)

#define MADC_CHANNEL_ADC0		0
#define MADC_CHANNEL_ADC1		1
#define MADC_CHANNEL_ADC2		2
#define MADC_CHANNEL_ADC3		3
#define MADC_CHANNEL_ADC4		4
#define MADC_CHANNEL_ADC5		5
#define MADC_CHANNEL_ADC6		6
#define MADC_CHANNEL_ADC7		7
#define ADMUX_CHANNEL_MASK		0xE0

#define MADC_PRESCALER_2		1
#define MADC_PRESCALER_4		2
#define MADC_PRESCALER_8		3
#define MADC_PRESCALER_16		4
#define MADC_PRESCALER_32		5
#define MADC_PRESCALER_64		6
#define MADC_PRESCALER_128		7
#define ADCSRA_PRESCALER_MASK 	0xF8
#define MADC_PRESCALER_CHOICE	MADC_PRESCALER_2

#define LEFT_ADJUST_ENABLE  	1//(1 for Enable,2 for Disable)

STD_error_t MADC_stderrInit(u8 ARG_u8VrefSelect,u8 ARG_uPreScalerSelect);
STD_error_t MADC_stderrStartConversion(u8 ARG_u8Channel);

void MADC_voidWaitFlag(void);
void MADC_voidClearFlag(void);

void MADC_voidAdcEnable(void);
void MADC_voidAdcDisable(void);

void MADC_voidAdcEnableInt(void);
void MADC_voidAdcDisableInt(void);

STD_error_t MADC_stderrRead(u16 * ARG_u16pReading,u8 ARG_u8Channel);

STD_error_t MADC_stderrSetCallBack(void (*ARG_pvoidfIsrFunc)(void));


STD_error_t MADC_stderrReadAsynch(u8 ARG_u8Channel);
u16 MADC_u16Reading(void);

// My functions

void MADC_voidInit(void);
u8 MADC_u8StartConversionSynch(u8 ARG_u8Channel);

#endif
