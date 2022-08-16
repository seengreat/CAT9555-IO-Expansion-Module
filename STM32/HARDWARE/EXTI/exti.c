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
#include "exti.h"
#include "gpio.h"
#include "delay.h"

unsigned char int_flag=0;

void EXTIX_Init(void)
{
   	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

    IO_Init();

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI3_IRQHandler(void)
{
    if(int_flag == 0)
    {
       int_flag = 1;
    }	
		EXTI_ClearITPendingBit(EXTI_Line3);
}
 
