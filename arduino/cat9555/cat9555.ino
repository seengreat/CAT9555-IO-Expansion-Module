/********************************
 * Seengreat CAT9555 IO Expansion Module demo
 * Author: Andy Li from Seengreat
 *******************************/

#include <string.h>
#include <stdlib.h> 
#include <Wire.h>

#define  DEV_ADDR   0X20  //when A2=0 A1=0 A0=0 =>0010 0000
#define  PIN_INT    2   //interrupt 0，pin of D2
//CAT9555 regsiter
#define IN_PORT0    0
#define IN_PORT1    1
#define OUT_PORT0   2
#define OUT_PORT1   3
#define PI_PORT0    4
#define PI_PORT1    5
#define CFG_PORT0   6
#define CFG_PORT1   7

unsigned char p0_val = 0x00;
unsigned char p1_val = 0xff; 
unsigned int t = 0; 
unsigned char int_flag = 0;
//Configure the serial port to use the standard printf function
//start
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}
//end


void Write_reg(unsigned char reg_addr, unsigned char value)
{
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(reg_addr);
    Wire.write(value);
    Wire.endTransmission();
}

unsigned char Read_reg(unsigned char reg_addr)
{
    Wire.beginTransmission(DEV_ADDR);
    Wire.write(reg_addr);
    Wire.endTransmission();
    Wire.requestFrom(DEV_ADDR,1);
    return  Wire.read();
}

void Read_pin_state(void)
{
   if( int_flag == 0)
   {
      int_flag = 1;
   }
}

void setup() 
{
   Serial.begin(115200);
   printf_begin();
   Wire.begin();

   pinMode(PIN_INT,INPUT_PULLUP); //按键设为输入模式,内部上拉
   attachInterrupt(0, Read_pin_state, FALLING); //下降沿触发中断 0，调用Read_pin_state 函数
   
   Write_reg(CFG_PORT0, 0x00);//set port 0 as output 
   Write_reg(CFG_PORT1, 0xFF);//set port 1 as input
   printf("cfg_port0:%x \r\n", Read_reg(CFG_PORT0));//read the configuration port 0 register
   printf("cfg_port1:%x \r\n", Read_reg(CFG_PORT1));//read the configuration port 1 register
   Write_reg(PI_PORT1, 0x00); 
  // put your setup code here, to run once:

}

void loop() 
{
   delay(20);
   t++;
   if(t>49)// Invert the level of the P0 port for about 1 second(20*50=1000ms)
   {
      t=0;
      p0_val =~p0_val;
      Write_reg(OUT_PORT0, p0_val);
   }
   if(int_flag == 1)//check the interrupt pin
   {
      char res = Read_reg(IN_PORT1);
      if(p1_val != res)//The level of port 1 has changed
      {
         p1_val = res;
         printf("port 1:%x \r\n", p1_val);
         int_flag = 0;
      }        
   }
}
