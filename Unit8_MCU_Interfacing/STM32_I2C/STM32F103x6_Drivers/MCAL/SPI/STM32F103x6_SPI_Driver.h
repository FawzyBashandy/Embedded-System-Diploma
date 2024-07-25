/*
 * STM32_F103C6_SPI_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32_F103C6_SPI_DRIVER_H_
#define STM32_F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include <BitMath.h>
#include <Platform_Types.h>
#include <STM32F103C6.h>
#include <stdint.h>

#include <NVIC/STM32F103x6_NVIC_Driver.h>
#include <RCC/STM32F103x6_RCC_Driver.h>
#include <GPIO/STM32F103x6_GPIO_Driver.h>

//-----------------------------
//General structures
//-----------------------------

typedef enum {SPIPolling,SPIInterrupt}SPIMechanism;

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	SPI_t * 	SPI;							/*Specify the instance of SPI required
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPIx_Define*/

	uint16_t 	DeviceMode;						/*Specify SPI_Device_Mode (Master or Slave)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_DeviceMode_Define*/

	uint16_t  	CommunicationMode;				/*Specify The required communication mode (Full Duplex / Half Duplex / Simplex)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_CommunicationMode_Define*/

	uint16_t   	FrameFormat;					/*Specify the Shifting method of Shift register (MSB First or LSB First)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_FrameFormat_Define
					   	  	  	  	  	  	  	  NOTE : must be the same as the master device*/

	uint16_t   	DataSize;						/*Specify the data size (8bit / 16bit)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_DataSize_Define*/

	uint16_t    	MasterClk;						/*Specify the frequency of master Clk
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_MasterCLK_Define
					   	  	  	  	  	  	  	  NOTE : this parameter is passed only when this device is MASTER*/

	uint16_t   	TimingConfig;					/*Specify the timing combination of Clk (Clock Phase and Polarity)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_TimingConfig_Define
					   	  	  	  	  	  	  	  NOTE : the timing configuration of both master and slave MUST be the same*/


	uint16_t	SS_Managment;					/*Specify the Slave Select Method (Handled by HW or SW)
												  This parameter must be a value of @ref SPI_SS_Managment_Define*/

	SPIMechanism  Mechanism_type;				/*Specify the Tx/Rx SPIMechanism	(Interrupt or otherwise)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref SPI_MechanismType_Define*/

}SPI_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref SPIx_Define

#define SPIx_Instance1									SPI1
#define SPIx_Instance2									SPI2
#define SPIx_Instance3									SPI3 //Not supported in STM32F103x6

//@ref SPI_DeviceMode_Define

#define SPI_DeviceMode_MASTER							(1<<2) 	//Master configuration
#define SPI_DeviceMode_SLAVE							0		//0: Slave configuration

//@ref SPI_CommunicationMode_Define

#define SPI_CommunicationMode_FULLDUPLEX				0					 //Full duplex (Transmit and receive)
#define SPI_CommunicationMode_FULLDUPLEX_RXONLY			(1<<10) 			 //Output disabled (Receive-only mode) for slave only
#define SPI_CommunicationMode_HALFDUPLEX_TXONLY			((1<<15) | (1<<14))  //1-line bidirectional data mode selected , Output enabled (transmit-only mode)
#define SPI_CommunicationMode_HALFDUPLEX_RXONLY			(1<<15) 			 //1-line bidirectional data mode selected , Output disabled (receive-only mode)


//@ref SPI_FrameFormat_Define

#define SPI_FrameFormat_MSBFirst						0		//MSB transmitted first
#define SPI_FrameFormat_LSBFirst						(1 << 7)//LSB transmitted first

//@ref SPI_DataSize_Define

#define SPI_DataSize_8b									0		//8-bit data frame format is selected for transmission/reception
#define SPI_DataSize_16b								(1<<11)	//16-bit data frame format is selected for transmission/reception

//@ref SPI_MasterCLK_Define

#define SPI_MasterCLK_Define_PCLKDiv2					0x0		//Output master clk is fPCLK/2   Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv4					(0x1<<3)//Output master clk is fPCLK/4   Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv8					(0x2<<3)//Output master clk is fPCLK/8   Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv16					(0x3<<3)//Output master clk is fPCLK/16  Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv32					(0x4<<3)//Output master clk is fPCLK/32  Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv64					(0x5<<3)//Output master clk is fPCLK/64  Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv128					(0x6<<3)//Output master clk is fPCLK/128 Max Frequency
#define SPI_MasterCLK_Define_PCLKDiv256					(0x7<<3)//Output master clk is fPCLK/256 Max Frequency


//@ref SPI_TimingConfig_Define

#define SPI_TimingConfig_C_Rising_T_Falling				0x00000000 //Capture data on First edge(Rising) and Transmit data on Second Edge (Falling)
#define SPI_TimingConfig_T_Rising_C_Falling				0x00000001 //Transmit data on First edge(Rising) and Capture data on Second Edge (Falling)
#define SPI_TimingConfig_C_Falling_T_Rising				0x00000002 //Capture data on First edge(Falling) and Transmit data on Second Edge (Rising)
#define SPI_TimingConfig_T_Falling_C_Rising				0x00000003 //Transmit data on First edge(Falling) and Capture data on Second Edge (Rising)



//@ref SPI_SS_Managment_Define

//Hardware Management
#define SPI_SS_Managment_Master_HW_OutputEnabled		(1<<2)	//SS output is disabled in master mode and the cell can work in multimaster configuration
#define SPI_SS_Managment_Master_HW_OutputDisabled		0		//SS output is enabled in master mode and when the cell is enabled. The cell cannot work in a multimaster environment.
#define SPI_SS_Mangament_Slave_HW						0
//Software Management
#define SPI_SS_Mangament_SW_NSS_SET        				((1<<9)|(1<<8))	  //Software slave management enabled and NSS is set to 1
#define SPI_SS_Mangament_SW_NSS_RESET        			(1<<9)	  		  //Software slave management enabled and NSS is set to 0

//@ref SPI_MechanismType_Define

#define SPI_MechanismType_POLLING			SPIPolling
#define SPI_MechanismType_Interrupt			SPIInterrupt


/////////////////////////////////////////////



#define SPI_IRQ_RXNE             6 //Transmit buffer empty
#define SPI_IRQ_TXE              7 //Receive buffer not empty
#define SPI_IRQ_MODF	    	 5 //Master Mode fault event
#define SPI_IRQ_OVR          	 4 //Overrun error
#define SPI_IRQ_CRCERR           3 //CRC error flag


/**************************************************************************************************************************
*===============================================
*         Control/Status Registers Pins Macros
*===============================================
*/

/*
*  SPI control register 1 (SPI_CR1) bit definitions.
*/
#define SPI_CR1_SPE       (1<<6)      	  /* SPI enable */

/*
*  SPI control register 2 (SPI_CR2) bit definitions.
*/
#define SPI_CR2_ERRIE     (1<<5)	//Error interrupt enable
#define SPI_CR2_RXNEIE    (1<<6)	//RX buffer not empty interrupt enable
#define SPI_CR2_TXEIE     (1<<7)	//Tx buffer empty interrupt enable






/*
*  SPI Status Register (SPI_SR) bit definitions.
*/
//OVR MODF CRCERR

#define SPI_SR_CRCERR       (1<<4)      	  /*CRC error flag*/
#define SPI_CR1_SPE_SET     (((uint16)0x0040))
#define SPI_SR_TXE          (((uint16)0x0002))
#define SPI_SR_RXNE         (((uint16)0x0001))
#define SPI_SR_BSY          (((uint16)0x0080))
#define SPI_SR_OVR          (((uint16)0x0040))
#define SPI_SR_MODF         (((uint16)0x0020))

#define SPI_TX_BUFFER_EMPTY       1
#define SPI_TX_BUFFER_FULL        0

#define SPI_RX_BUFFER_EMPTY       0
#define SPI_RX_BUFFER_FULL        1

/*
* ===============================================
* APIs Supported by "MCAL SPI DRIVER"
* ===============================================
*/
void MCAL_SPI_Init(SPI_Config_t * SPIx);
void MCAL_SPI_DeInit(SPI_Config_t * SPIx);
void MCAL_SPI_SendData(SPI_Config_t * SPIx , uint16_t * data);
void MCAL_SPI_ReceiveData(SPI_Config_t * SPIx , uint16_t * data);
void MCAL_SPI_ExchangeData(SPI_Config_t * SPIx , uint16_t * data);
void MCAL_SPI_Enable_Interrupt(SPI_Config_t * SPIx , uint8_t IRQ_Event , void ( * P_IRQEvent_CallBack)(void));
void MCAL_SPI_Interrupt_Disable(SPI_Config_t * SPI, uint8_t IRQ_Event);
uint8_t is_SPI_BSY(SPI_Config_t * SPIcfg);
#endif /* STM32_F103C6_SPI_DRIVER_H_ */
