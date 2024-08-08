/*
 * ATmega32_ADC.h
 *
 * Created: 31/01/2024 01:02:40 ص
 *  Author: fawzy
 */ 


#ifndef ATMEGA32_ADC_H_
#define ATMEGA32_ADC_H_

//-----------------------------
//Includes
//-----------------------------

#include "ATmega32.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

/** 
 * @defgroup ADC_Mode_Define
 * @{
 */
typedef enum eADC_Mode
{	
	SingleConversion,								//Conversion is triggered explicitly
	AutoTriggerConversion = ADC_ADCSRA_ADATE_MSK	//Conversion is done automatically by trigger event, Note you must specify the trigger event
}eADC_Mode;
/** @} */
#define ASSERT_ADC_MODE(mode)	((SingleConversion			== mode)    || \
								 (AutoTriggerConversion		== mode))

/** 
 * @defgroup ADC_Clock_Define
 * @{
 */
typedef enum 
{
	ADC_PreScaler_2 = 1,					/*!<CLKinput/2*/ 
	ADC_PreScaler_4,						/*!<CLKinput/4*/
	ADC_PreScaler_8,						/*!<CLKinput/8*/ 
	ADC_PreScaler_16,						/*!<CLKinput/16*/
	ADC_PreScaler_32,						/*!<CLKinput/32*/
	ADC_PreScaler_64,						/*!<CLKinput/64	*/
	ADC_PreScaler_128,						/*!<CLKinput/128*/

}eADC_Clock;
/** @} */

#define ASSERT_ADC_CLK(CLK)	   (ADC_PreScaler_2 <= CLK &&  \
							   (ADC_PreScaler_128 >= CLK))


/** 
* @defgroup ADC_Trigger_Define
* @{
*/
typedef enum
{
	EndofConversionFlag_Trigger,      /*!< Continuous triggering: The next conversion starts at the end of the previous conversion (ADIF Flag) */
	AnalogComparator_Trigger,         /*!< Triggered by an analog comparator; behavior depends on ADC Mode */
	ExternalInterrupt0_Trigger,       /*!< Triggered by an external interrupt on INT0 */
	Timer0CompareMatch_Trigger,       /*!< Triggered when Timer0 reaches the compare match value */
	Timer0Overflow_Trigger,           /*!< Triggered when Timer0 overflows */
	Timer1CompareMatch_Trigger,       /*!< Triggered when Timer1 reaches the compare match value */
	Timer1Overflow_Trigger,           /*!< Triggered when Timer1 overflows */
	Timer1CaptureEvent_Trigger        /*!< Triggered by a capture event on Timer1 */

} eADC_Trigger;
/** @} */

#define ASSERT_ADC_Trigger(Trigger) ((EndofConversionFlag_Trigger	== Trigger)		|| \
									(AnalogComparator_Trigger		== Trigger)     || \
									(ExternalInterrupt0_Trigger		== Trigger)     || \
									(Timer0CompareMatch_Trigger		== Trigger)		|| \
									(Timer0Overflow_Trigger			== Trigger)     || \
									(Timer1CompareMatch_Trigger		== Trigger)     || \
									(Timer1Overflow_Trigger			== Trigger)		|| \
									(Timer1CaptureEvent_Trigger		== Trigger))
/** 
 * @defgroup ADC_ReferenceVoltage_Define
 * @{
 */
typedef enum {
	AREF,																/*!< AREF, Internal Vref turned off */
	AVCC			= ADC_ADMUX_REFS0_MSK,								/*!< AVCC with external capacitor at AREF pin*/
	InternalVoltage = ADC_ADMUX_REFS0_MSK | ADC_ADMUX_REFS1_MSK			/*!< Internal 2.56V Voltage Reference with external capacitor at AREF pin*/
}eADC_ReferenceVoltageSRC;
/** @} */

#define ASSERT_ADC_ReferenceVoltage(Vrf)	((AREF				== Vrf)    || \
											(AVCC				== Vrf)	   || \
											(InternalVoltage	== Vrf))
/** 
 * @defgroup ADC_DataAdjustment_Define
 * @{
 */
typedef enum {
	RightAdjusted,                     /*!< Data is right-adjusted in the ADC data registers */
	LeftAdjusted = ADC_ADMUX_ADLAR_MSK /*!< Data is left-adjusted in the ADC data registers */
} eADC_DataAdjustment;
/** @} */

#define ASSERT_ADC_DataAdjustmen(DA)		((RightAdjusted				== DA)    || \
											 (LeftAdjusted				== DA))

/** 
 * @defgroup ADC_InputChannel_Define
 * @{
 */
typedef enum{
    ADC_Channel_0,                          /*!<Single ended input channel 0*/
    ADC_Channel_1,                          /*!<Single ended input channel 1*/
    ADC_Channel_2,                          /*!<Single ended input channel 2*/
    ADC_Channel_3,                          /*!<Single ended input channel 3*/
    ADC_Channel_4,                          /*!<Single ended input channel 4*/
    ADC_Channel_5,                          /*!<Single ended input channel 5*/
    ADC_Channel_6,                          /*!<Single ended input channel 6*/
    ADC_Channel_7,                          /*!<Single ended input channel 7*/

    ADC_Channel_POS0_NEG0_10x,              /*!<Differential input channel (0 +ve), (0 -ve), Gain 10x*/
    ADC_Channel_POS1_NEG0_10x,              /*!<Differential input channel (1 +ve), (0 -ve), Gain 10x*/
    ADC_Channel_POS0_NEG0_200x,             /*!<Differential input channel (0 +ve), (0 -ve), Gain 200x*/
    ADC_Channel_POS1_NEG0_200x,             /*!<Differential input channel (1 +ve), (0 -ve), Gain 200x*/
    ADC_Channel_POS2_NEG2_10x,              /*!<Differential input channel (2 +ve), (2 -ve), Gain 10x*/
    ADC_Channel_POS3_NEG2_10x,              /*!<Differential input channel (3 +ve), (2 -ve), Gain 10x*/
    ADC_Channel_POS2_NEG2_200x,             /*!<Differential input channel (2 +ve), (2 -ve), Gain 200x*/
    ADC_Channel_POS3_NEG2_200x,             /*!<Differential input channel (3 +ve), (2 -ve), Gain 200x*/

    ADC_Channel_POS0_NEG1,                  /*!<Differential input channel (0 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS1_NEG1,                  /*!<Differential input channel (1 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS2_NEG1,                  /*!<Differential input channel (2 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS3_NEG1,                  /*!<Differential input channel (3 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS4_NEG1,                  /*!<Differential input channel (4 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS5_NEG1,                  /*!<Differential input channel (5 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS6_NEG1,                  /*!<Differential input channel (6 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS7_NEG1,                  /*!<Differential input channel (7 +ve), (1 -ve), Gain 1x*/

    ADC_Channel_POS0_NEG2,                  /*!<Differential input channel (0 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS1_NEG2,                  /*!<Differential input channel (1 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS2_NEG2,                  /*!<Differential input channel (2 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS3_NEG2,                  /*!<Differential input channel (3 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS4_NEG2,                  /*!<Differential input channel (4 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS5_NEG2,                  /*!<Differential input channel (5 +ve), (2 -ve), Gain 1x*/
    
    ADC_Channel_VBG,                        /*!<Single ended input channel 1.22V*/
    ADC_Channel_GND							/*!<Single ended input channel 0V*/
}eADC_InputChannel;
/** @} */

#define ASSERT_ADC_InputChannel(IC)			((IC >= 0) && (IC <= 31))

/**
 * @brief Configuration structure for ADC
 */
typedef struct
{
    eADC_Clock					Clock;						/*< Specifies the ADC Clock  
																This parameter must be a value of @ref ADC_Clock_Define */
			
	eADC_Mode					conversionMode;				/*< Specifies the ADC Conversion Mode (Single Conversion or AutoTrigger conversion)
																This parameter must be a value of @ref ADC_Mode_Define */
	
	eADC_DataAdjustment			dataAdjustment;				/*< Specifies the ADC Data reigsters adjustment wether it's left or right
																This parameter must be a value of @ref ADC_DataAdjustment_Define */
	
	eADC_InputChannel			inputChannel;				/*< Specifies the ADC Analog Input Channel (ADCx)
																This parameter must be a value of @ref ADC_InputChannel_Define */
	
	eADC_ReferenceVoltageSRC	referenceVoltage;			/*< Specifies the ADC reference voltage (Vref)
																This parameter must be a value of @ref ADC_ReferenceVoltage_Define */
	
	eADC_Trigger				conversionTriggerEvent;		/*< Specifies the Trigger event that will trigger conversion in case of AutoTrigger Conversion mode only
																This parameter must be a value of @ref ADC_Trigger_Define */
} ADC_Config_t;

typedef enum{
	E_OK,
	E_NOK
}eStatus_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL ADC DRIVER"
*===============================================
*/

eStatus_t MCAL_ADC_Init(ADC_Config_t* ADCcfg);
eStatus_t MCAL_ADC_Reset();
eStatus_t MCAL_ADC_startConversion();
eStatus_t MCAL_ADC_autoConversionStop();
eStatus_t MCAL_ADC_changeInputChannel(eADC_InputChannel channel);
eStatus_t MCAL_ADC_getConversionResult(uint16_t* pBuffer);
eStatus_t MCAL_ADC_setEndOfConversion_CALLBACK(void (*callback)(void));
#endif /* ATMEGA32_ADC_H_ */