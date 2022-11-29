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
 * Author		   :Andy Li
 * Web Site		   :www.seengreat.com
***************************************************************************************/
#include "sys.h"
#include "usart.h"
#include "gpio.h"
#include "delay.h"
#include "cat9555.h"
#include "myiic.h"
#include "exti.h"

extern unsigned char int_flag;

int main(void)
{
	char p0_val = 0x00;
	char p1_val = 0xff;
	unsigned char res = 0;
	unsigned int t = 0;
	SystemInit();
	Uart1Init(9600,0,0);
	printf("\r\n---------- CAT9555 IO Expansion Module ----------\r\n");
	printf("STM32F103C8T6 ");
	printf("V1.0.0 Build 2022/06/28 09:22\r\n");
	EXTIX_Init();
	delay_init();
	IIC_Init();
	Write_reg(CFG_PORT0, 0x00);//set the port 0 as output
	Write_reg(CFG_PORT1, 0xFF);//set the port 1 as intput
	printf("cfg_port0:%x \r\n", Read_reg(CFG_PORT0));//read the configuration port 0 register
	printf("cfg_port1:%x \r\n", Read_reg(CFG_PORT1));//read the configuration port 1 register
	Write_reg(PI_PORT1, 0x00);
	while(1)
	{
			delay_ms(20);
			t++;
			if(t>49)//Invert the level of the P0 for about 1 second(20*50=1000ms)
			{
					t = 0;
					p0_val = ~p0_val;
					Write_reg(OUT_PORT0, p0_val);
			} 
			if(int_flag == 1) //check the interrupt pin state
			{
					res = Read_reg(IN_PORT1);
					if(p1_val != res)//The level of P1 has changed
					{
							p1_val = res;
							printf("port 1:%x\r\n",p1_val);
							int_flag = 0;
					}
			}
	 }
}

