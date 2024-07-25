/*
 * LCD_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */




#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include <GPIO/STM32F103x6_GPIO_Driver.h>
#include "STM32F103C6.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	GPIO_t * LCD_dataPort;      /*Specify the GPIO that's connected to the LCD DATA PINS
								 *This Parameter must be a value of @ref LCD_Port_Define*/


	GPIO_t * LCD_ctrlPort;		/*Specify the GPIO that's connected to the LCD CTRL PINS
								 *This Parameter must be a value of @ref LCD_Port_Define*/

	uint16_t dataPins;			 /*Specify the pins that will be connected to DataPins (D0..D7)
					   	  	  	   This paramerter must be a value of @ref LCD_DPINS_Define*/


	uint16_t ctrlPins;			/*Specify the pins that will be connected to ctrlPins (RS,RW,EN)
					   	  	  	   This paramerter must be a value of @ref LCD_CPINS_Define*/

	uint8_t	 LCD_Mode;			/*Specify the mode of the LCD wether it's 8 bit mode or 4 bit mode
								  This parameter must be a value of @ref LCD_MODE_Define*/
}LCD_Config;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref LCD_DPINS_Define
#define LCD_DPINS_LOWER_HALF 		0x000000FFUL	   //Write to select the lower half pins 	(Px0->(D0)....Px7 ->(D7))  where x is any available GPIO PORT (A,B,..)
#define LCD_DPINS_HIGHER_HALF		0x0000FF00UL	   //Write to select the higher half pins 	(Px8->(D0)....Px15->(D7)) where x is any available GPIO PORT (A,B,..)

//*4BITMODE ONLY
#define LCD_DPINS_FIRST_NIBBLE		0x0000000FUL	   //4BITMODE ONLY : Write to select the first 4 bits of the selected ports 	(Px0->(D5)....Px3  ->(D7))  where x is the chosen data port
#define LCD_DPINS_SECOND_NIBBLE		0x000000F0UL	   //4BITMODE ONLY : Write to select the Second 4 bits of the selected ports 	(Px4->(D5)....Px7  ->(D7))  where x is the chosen data port
#define LCD_DPINS_THIRD_NIBBLE		0x00000F00UL	   //4BITMODE ONLY : Write to select the Third 4 bits of the selected ports 	(Px8->(D5)....Px11 ->(D7))  where x is the chosen data port
#define LCD_DPINS_FOURTH_NIBBLE		0x0000F000UL	   //4BITMODE ONLY : Write to select the Fourth 4 bits of the selected ports 	(Px12->(D5)...Px15 ->(D7))  where x is the chosen data port

//@ref LCD_CPINS_Define
#define LCD_CPINS_G1 				0x00000007UL	   //Write to select the (Px0  as RS , 	Px1  as RW , Px2  as EN)  where x is any available GPIO PORT (A,B,..)
#define LCD_CPINS_G2 				0x00000038UL	   //Write to select the (Px3  as RS , 	Px4  as RW , Px5  as EN)  where x is any available GPIO PORT (A,B,..)
#define LCD_CPINS_G3 				0x000001C0UL	   //Write to select the (Px6  as RS ,	Px7  as RW , Px8  as EN)  where x is any available GPIO PORT (A,B,..)
#define LCD_CPINS_G4 				0x00000E00UL	   //Write to select the (Px9  as RS , 	Px10 as RW , Px11 as EN)  where x is any available GPIO PORT (A,B,..)
#define LCD_CPINS_G5 				0x00007000UL	   //Write to select the (Px12 as RS , 	Px13 as RW , Px14 as EN)  where x is any available GPIO PORT (A,B,..)

//@ref LCD_Port_Define
#define LCD_PORT_GPIOA				GPIOA			   //Write to select GPIOA Port as the port that's connected to LCD DATA PINS 	(Px0....Px7)  where x is any available GPIO PORT (A,B,..)
#define LCD_PORT_GPIOB				GPIOB			   //Write to select GPIOB Port as the port that's connected to LCD DATA PINS 	(Px0....Px7)  where x is any available GPIO PORT (A,B,..)
#define LCD_PORT_GPIOC				GPIOC			   //Do not use in case of LQF48:Write to select GPIOC Port as the port that's connected to LCD DATA PINS 	(Px0....Px7)  where x is any available GPIO PORT (A,B,..)
#define LCD_PORT_GPIOD				GPIOD			   //Do not use in case of LQF48:Write to select GPIOD Port as the port that's connected to LCD DATA PINS 	(Px0....Px7)  where x is any available GPIO PORT (A,B,..)
/*NOTE : you have to make sure that the selected port in LCD_dataPort parameter has the dataPins that you selected as some ports doesn't have all the pins out of MCU*/

//@ref LCD_MODE_Define
#define LCD_MODE_8BIT				1					//Write to select LCD MODE as 8bit mode (D0..D7)
#define LCD_MODE_4BIT				0					//Write to select LCD MODE as 4bit mode (D4..D7)
/*
* ===============================================
* APIs Supported by "HAL LCD DRIVER"
* ===============================================
*/
void HAL_LCD_Init(LCD_Config * lcdConfig);
void HAL_LCD_Clear_Screen(LCD_Config * lcdConfig);
void HAL_LCD_WRITE_COMMAND(LCD_Config * lcdConfig,uint8_t command);
void HAL_LCD_WRITE_CHAR(LCD_Config * lcdConfig,uint8_t character);
void HAL_LCD_WRITE_STRING(LCD_Config * lcdConfig,uint8_t* string);
void HAL_LCD_check_isbusy(LCD_Config * lcdConfig);
void HAL_LCD_Kick(LCD_Config * lcdConfig);
void HAL_LCD_GOTO_XY(LCD_Config * lcdConfig , uint8_t line, uint8_t position);
void HAL_LCD_Display_Number(LCD_Config * lcdConfig,int32_t number);
void HAL_LCD_Display_Real_Number(LCD_Config * lcdConfig,float64 num);


#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_ROW						(0x80)
#define LCD_BEGIN_AT_SECOND_ROW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)

#endif /* LCD_DRIVER_H_ */
