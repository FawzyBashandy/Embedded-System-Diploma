/*
 * ATmega32_Timer0.h
 *
 * Created: 31/01/2024 01:02:40 ص
 *  Author: fawzy
 */ 


#ifndef ATMEGA32_TIMER0_H_
#define ATMEGA32_TIMER0_H_

//-----------------------------
//Includes
//-----------------------------

#include "ATmega32.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

/** 
 * @defgroup TIMER0_OperationMode_Define
 * @{
 */
enum eTimerMode
{	
	NormalMode,
	PhaseCorrectPWM_Mode	= TIMER0_TCCR_WGM0_MSK,
	ClearOnCompareMatchMode = TIMER0_TCCR_WGM1_MSK,
	FastPWM_Mode			= (TIMER0_TCCR_WGM1_MSK | TIMER0_TCCR_WGM0_MSK)
};
/** @} */
#define ASSERT_TIMER_MODE(mode) ((NormalMode				== mode)    || \
								 (PhaseCorrectPWM_Mode		== mode)    || \
								 (ClearOnCompareMatchMode	== mode)    || \
								 (FastPWM_Mode				== mode))

/** 
 * @defgroup TIMER0_ClockSource_Define
 * @{
 */
enum eTimer_CLK_SRC
{
	Timer_No_CLKSRC,																			/*!< No clock source (Timer/Counter stopped).*/  
	Timer_PreScaler_1,												/*!<clkIO/1		(No prescaling)*/ 
	Timer_PreScaler_8,												/*!<clkIO/8		(From prescaler)*/ 
	Timer_PreScaler_64,						/*!<clkIO/64	(From prescaler)*/
	Timer_PreScaler_256,												/*!<clkIO/256	(From prescaler)*/
	Timer_PreScaler_1024,						/*!<clkIO/1024  (From prescaler)*/
	Timer_EXT_CLK_Falling,						/*!<External clock source on T0 pin. Clock on falling edge.*/
	Timer_EXT_CLK_Rising	/*!<External clock source on T0 pin. Clock on rising edge*/

};
/** @} */

#define ASSERT_TIMER_CLK(CLK)  (Timer_No_CLKSRC <= CLK &&  \
							   (Timer_EXT_CLK_Rising >= CLK))

/************************
/*<! TIMER_COM_DEFINE >*/

/** 
 * @defgroup in case of Non-PWM Mode
 * @{
 */
/**
 * Timer_COM              : Description
 * Timer_COM_Disconnected : Normal port operation, OC0 disconnected.
 * Timer_COM_Toggle       : Toggle OC0 on Compare Match
 * Timer_COM_Clear        : Clear OC0 on Compare Match
 * Timer_COM_Set          : Set OC0 on Compare Match
 /** @} */
 
 /** 
 * @defgroup in case of Fast PWM mode
 * @{
 */
/**
 * Timer_COM              : Description
 * Timer_COM_Disconnected : Normal port operation, OC0 disconnected.
 * RESERVED				  -> Do not use it
 * Timer_COM_Clear        : Clear OC0 on Compare Match, set OC0 at BOTTOM, ((non-inverting mode)
 * Timer_COM_Set          : Set OC0 on Compare Match, clear OC0 at BOTTOM, (inverting mode)
 /** @} */
  
 /** 
 * @defgroup in case of PWM mode
 * @{
 */
/**
 * Timer_COM              : Description
 * Timer_COM_Disconnected : Normal port operation, OC0 disconnected.
 * RESERVED				  -> Do not use it
 * Timer_COM_Clear        : Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting
 * Timer_COM_Set          : Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting.
 /** @} */
 
enum eTimer_COM_Mode
{
	Timer_COM_Disconnected,														/*!< Refer to the above references to know actual behavior , The behavior depends on Timer0 Mode*/
	Timer_COM_Toggle	=TIMER0_TCCR_COM0_MSK,									/*!< Refer to the above references to know actual behavior , The behavior depends on Timer0 Mode*/
	Timer_COM_Clear		=TIMER0_TCCR_COM1_MSK,									/*!< Refer to the above references to know actual behavior , The behavior depends on Timer0 Mode*/
	Timer_COM_Set		=TIMER0_TCCR_COM0_MSK | TIMER0_TCCR_COM1_MSK			/*!< Refer to the above references to know actual behavior , The behavior depends on Timer0 Mode*/

};
/** @} */

#define ASSERT_TIMER_COM(com)  ((Timer_COM_Disconnected == com)     || \
								(Timer_COM_Toggle       == com)     || \
								(Timer_COM_Clear        == com)     || \
								(Timer_COM_Set          == com))

/** 
 * @defgroup TIMER0_OverFlowInterrupt_Define
 * @{
 */
enum eTimer_TOIE{
	Timer_TOI_Disable,                                              /*!< Timer Overflow interrupt disable */
	Timer_TOI_Enable = TIMER0_TIMSK_TOIE0_MSK						/*!< Timer Overflow interrupt enable*/
};
/** @} */

#define ASSERT_TIMER_TOIE(TOIE) ((Timer_TOI_Disable == TOIE)     || \
								 (Timer_TOI_Enable  == TOIE))
/** 
 * @defgroup TIMER0_CompareMatchInterrupt_Define
 * @{
 */
enum eTimer_TOCIE{
	Timer_TOCI_Disable,                                          /*!< Timer Overflow interrupt disable */
	Timer_TOCI_Enable = TIMER0_TIMSK_OCIE0_MSK					 /*!< Timer Output compare match interrupt enable*/
};
/** @} */

#define ASSERT_TIMER_TOCIE(TOCIE) ((Timer_TOCI_Disable == TOCIE)     || \
								   (Timer_TOCI_Enable  == TOCIE))
/**
 * @brief Configuration structure for Timer0
 */
typedef struct
{
    enum eTimer_CLK_SRC		ClockSource;			 /*< Specifies the Timer0 Clock input source 
														 This parameter must be a value of @ref TIMER0_ClockSource_Define */
			
	enum eTimerMode			OperationMode;			/*< Specifies the Timer0 Operation Mode (Normal ,...,...,...)
														This parameter must be a value of @ref TIMER0_OperationMode_Define */
	
	enum eTimer_COM_Mode	CompareMode;			/*< Specifies the Timer0 Compare Match Output Unit Behavior 
														This parameter must be a value of @ref TIMER0_CompareMode_Define */
	
	enum eTimer_TOIE		OverFlowInterrupt;		/*< Specifies the Timer0 OverFlow interrupt status (Enable or Disable) 
														This parameter must be a value of @ref TIMER0_OverFlowInterrupt_Define */
							
	enum eTimer_TOCIE		CompareMatchInterrupt;	/*< Specifies the Timer0 CompareMatch interrupt status (Enable or Disable)
														This parameter must be a value of @ref TIMER0_CompareMatchInterrupt_Define */
	
} Timer0_Config_t;

typedef enum{
	E_OK,
	E_NOK
}eStatus_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL Timer0 DRIVER"
*===============================================
*/

eStatus_t MCAL_TIMER0_Init(Timer0_Config_t* timerCFG);
eStatus_t MCAL_TIMER0_Stop();
eStatus_t MCAL_TIMER0_GetCompare(uint8_t* compareVal);
eStatus_t MCAL_TIMER0_SetCompare(uint8_t compareVal);
eStatus_t MCAL_TIMER0_GetCounter(uint8_t* counterVal);
eStatus_t MCAL_TIMER0_SetCounter(uint8_t counterVal);
eStatus_t MCAL_TIMER0_GetOverflow(uint32_t* overflowVal);
eStatus_t MCAL_TIMER0_SetOverflow(uint32_t overflowVal);
void MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(void (*callback)(void));
void MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(void (*callback)(void));
#endif /* ATMEGA32_TIMER0_H_ */