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
#include "cat9555.h"
#include "delay.h"
#include "myiic.h"

void RC522_WR_Reg(u8 RCsla,u8 addr,u8 val)
{
	IIC_Start();  				 
	IIC_Send_Byte(RCsla);     	
	IIC_Wait_Ack();	   
  IIC_Send_Byte(addr);
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(val);     			   
	IIC_Wait_Ack();  		    	   
  IIC_Stop();				
}

unsigned char RC522_RD_Reg(u8 RCsla,u8 addr)
{
	u8 temp=0;		 
	IIC_Start();  				 
	IIC_Send_Byte(RCsla);	
	temp=IIC_Wait_Ack();	   
  IIC_Send_Byte(addr);   	
	temp=IIC_Wait_Ack(); 	 										  		   
	IIC_Start();  	 	   		
	IIC_Send_Byte(RCsla+1);	 
	temp=IIC_Wait_Ack();	   
  temp=IIC_Read_Byte(0);		    	   
  IIC_Stop();				 
	return temp;			
}  

unsigned char Read_reg(unsigned char Address)
{
	unsigned char ucResult;
	ucResult = RC522_RD_Reg(I2C_ADDR,Address);    //read reg
	return ucResult;
}

void Write_reg(unsigned char Address, unsigned char value)
{
	RC522_WR_Reg(I2C_ADDR,Address,value);
}

