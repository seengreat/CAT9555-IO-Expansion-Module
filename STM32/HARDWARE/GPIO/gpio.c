/***************************************************************************************
 * Project  :CAT9555-IIC-STM32
 * Describe :Use IIC for I/O port expansion.
 *			 The P0 level is flipped every second.
 *			 Press the P1 key to enter the interrupt
 * Experimental Platform :STM32F103C8T6 + CAT9555 IO Expansion Module
 * Hardware Connection :STM32f103 -> CAT9555 IO Expansion Module
 *			3V3	 ->	VCC					PB10 -> SCL1
 *			GND	 ->	GND					PB11 -> SDA1
 *			PB3	 ->	/INT
 * Library Version :ST_V3.5
 * Author		   :Christian
 * Web Site		   :www.seengreat.com
***************************************************************************************/
#include "gpio.h"

void IO_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
} 

