/*
 * STM32_F103C6_I2C_Driver.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32_F103C6_I2C_DRIVER_H_
#define STM32_F103C6_I2C_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include <BitMath.h>
#include <Platform_Types.h>
#include <STM32F103C6.h>
#include <stdint.h>

#include <GPIO/STM32F103x6_GPIO_Driver.h>
#include <NVIC/STM32F103x6_NVIC_Driver.h>
#include <RCC/STM32F103x6_RCC_Driver.h>

//-----------------------------
//General Enumerations and Structures
//-----------------------------
/** @brief I2C mechanism types. */
typedef enum {
    I2CInterrupt, /**< Interrupt-based mechanism. */
    I2CPolling    /**< Polling-based mechanism. */
} eI2CMechanism_t;

/** @brief I2C addressing modes. */
typedef enum {
    SingleAddress, /**< Single address mode. */
    DualAddress    /**< Dual address mode. */
} eI2CAddressingMode_t;

/** @brief I2C address lengths. */
typedef enum {
    SevenBits = 7, /**< 7-bit address. */
    TenBits = 10   /**< 10-bit address. */
} ei2CAddressLength_t;

/** @brief I2C start condition types. */
typedef enum {
    RepeatedStart, /**< Repeated start condition. */
    NormalStart    /**< Normal start condition. */
} eStart_t;

/** @brief I2C stop condition types. */
typedef enum {
    StopConditionEnable,  /**< Enable stop condition. */
    StopConditionDisable  /**< Disable stop condition. */
} eStop_t;

/** @brief Status enumeration. */
typedef enum {
    RESET, /**< Flag/reset state. */
    SET    /**< Flag/set state. */
} eStatus_t;

/** @brief I2C data direction types. */
typedef enum {
    MasterTransmits, /**< Master transmits data. */
    MasterReceives   /**< Master receives data. */
} eDataDir_t;

/** @brief I2C interrupt types. */
typedef enum {
    StartBitSentInterrupt,                 /**< Start bit sent (Master). */
    AddressSentorMatchedInterrupt,         /**< Address sent (Master) or Address matched (Slave). */
    StopReceivedInterrupt,                 /**< Stop received (Slave). */
    DataByteTransferFinishedInterrupt,     /**< Data byte transfer finished. */
    ReceiverBufferNotEmpty,                /**< Receive buffer not empty. */
    TransmitterBufferEmpty                 /**< Transmit buffer empty. */
} Interruptx;

/** @brief I2C flags enumeration. */
typedef enum {
    I2C_Busy_Flag,     /**< I2C bus busy flag. */
    I2C_EV5,          /**< Start bit flag (SB). */
    I2C_EV6,          /**< Address flag (ADDR). */
    I2C_EV7,          /**< Receive buffer not empty flag (RXNE). */
    I2C_EV8,          /**< Transmit buffer empty flag (TXE). */
    I2C_EV8_1,
    I2C_EV8_2         /**< Transmit buffer empty and Byte transfer finished flags (TXE and BTF). */
} eI2CFlags_t;

/** @brief Structure for I2C address configuration. */
typedef struct {
    uint16_t Primary_Address;     /**< Primary address of the slave. */
    uint16_t Secondary_Address;   /**< Secondary address of the slave (used in dual address mode). */
    eI2CAddressingMode_t Mode;    /**< Addressing mode (single or dual). */
    ei2CAddressLength_t Length;   /**< Address length (7-bit or 10-bit). */
} sI2CAddress_t;

/** @brief Structure for master transmission/reception configuration. */
typedef struct {
    eStart_t StartCondition;      /**< Start condition type. */
    eStop_t StopCondition;        /**< Stop condition type. */
    eDataDir_t Direction;         /**< Data direction (transmit or receive). */
    sI2CAddress_t AddressCFG;    /**< Address configuration. */
    uint8_t * DataBuffer;         /**< Pointer to the data buffer. */
    uint32_t DataBufferLength;    /**< Length of the data buffer. */
} sMasterTxRx_t;

//-----------------------------
// User Type Definitions (Structures)
//-----------------------------


typedef struct
{
	I2C_t * 	I2C;							/*Specify the instance of I2C required
												  This Parameter must be a value of @ref I2C_Define*/

	uint16_t 	Mode;							/*Specify the I2C Speed mode
	 	 	 	 	 	 	 	 	 	 	 	  This parameter must be a value of @ref I2C_Mode_Define*/

	uint32_t    ClockSpeed;						/*Specify the Clock speed of I2C(SCL)
												  This parameter must be a value of @ref I2C_ClockSpeed_Define*/

	sI2CAddress_t * SlaveAddress;


	uint16_t	ClockStretching; 				/*Specify the Clock stretching functional state
												  This parameter must be a value of @ref I2C_ClockStretching_Define*/

	uint16_t 	GeneralCallAddress;				/*Specify the General Call Address Functional State
												  This parameter must be a value of @ref I2C_GeneralCallAddress_Define*/

	eI2CMechanism_t Mechanism;					/*Specify the transmission and receiving mechanism whether it's interrupt or polling
												  This parameter Must be a value of @ref I2C_Mechanism_Define*/

}I2C_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref I2C_Define

#define I2C_Instance1									I2C1
#define I2C_Instance2									I2C2

//@ref I2C_Mode_Define

#define I2C_Mode_SM										0x0 	 //Sm mode I2C
#define I2C_Mode_FM										(1 << 15)//Fm mode I2C :-> Fast mode not supported

/*-----------@ref  I2C_ClockSpeed_DEFINE----------*/
/*Note: Fast Mode isn't supported*/
#define I2C_ClockSpeed_SM10KHZ            				10000UL // I2C -> Standard Mode -> 10KHZ  SCL
#define I2C_ClockSpeed_SM20KHZ            				20000UL // I2C -> Standard Mode -> 20KHZ  SCL
#define I2C_ClockSpeed_SM30KHZ            				30000UL // I2C -> Standard Mode -> 30KHZ  SCL
#define I2C_ClockSpeed_SM40KHZ            				40000UL // I2C -> Standard Mode -> 40KHZ  SCL
#define I2C_ClockSpeed_SM50KHZ            				50000UL // I2C -> Standard Mode -> 50KHZ  SCL
#define I2C_ClockSpeed_SM60KHZ            				60000UL // I2C -> Standard Mode -> 60KHZ  SCL
#define I2C_ClockSpeed_SM70KHZ            				70000UL // I2C -> Standard Mode -> 70KHZ  SCL
#define I2C_ClockSpeed_SM80KHZ            				80000UL // I2C -> Standard Mode -> 80KHZ  SCL
#define I2C_ClockSpeed_SM90KHZ            				90000UL // I2C -> Standard Mode -> 90KHZ  SCL
#define I2C_ClockSpeed_SM100KHZ           				100000UL// I2C -> Standard Mode -> 100KHZ SCL

//@ref I2C_ClockStretching_Define

#define I2C_ClockStretching_Enable						0		//Clock stretching enabled
#define I2C_ClockStretching_Disable						(1 << 7)//Clock stretching disabled

//@ref I2C_GeneralCallAddress_Define

#define I2C_GeneralCallAddress_Disable					0		//General call disabled. Address 00h is NACKed.
#define I2C_GeneralCallAddress_Enable					(1 << 6)//General call enabled. Address 00h is ACKed.

//@ref I2C_Mechanism_Define

#define I2C_Mechanism_Polling						I2CPolling
#define I2C_Mechanism_Interrupt						I2CInterrupt



/**************************************************************************************************************************
*===============================================
*         Control/Status Registers Pins Macros
*===============================================
*/
/*
* ===============================================
* APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/
void MCAL_I2C_Init(I2C_Config_t * I2Cx);
void MCAL_I2C_DeInit(I2C_Config_t * I2Cx);
void MCAL_I2C_Master_TX(I2C_Config_t * I2Cx , sMasterTxRx_t * MasterCFG );
void MCAL_I2C_Master_RX(I2C_Config_t * I2Cx , sMasterTxRx_t * MasterCFG );
void MCAL_I2C_SlaveTx(I2C_Config_t * I2Cx , uint8_t data);
uint8_t MCAL_I2C_SlaveRx(I2C_Config_t * I2Cx);
void MCAL_I2C_Interrupt_Enable(I2C_Config_t * I2Cx, Interruptx Interrupt , void ( * P_IRQEvent_CallBack)(void));
void MCAL_I2C_Interrupt_Disable(I2C_Config_t * I2Cx, Interruptx Interrupt);


#endif /* STM32_F103C6_I2C_DRIVER_H_ */
