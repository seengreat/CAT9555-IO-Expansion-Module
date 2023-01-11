/***********************************
 * Seengreat CAT9555 IO Expansion Module demo
 * Author(s):Andy Li from Seengreat
 * ********************************/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define  DEV_ADRR   0x27  //when A2=1 A1=1 A0=1 =>0010 0111

//CAT9555 regsiter
#define IN_PORT0    0
#define IN_PORT1    1
#define OUT_PORT0   2
#define OUT_PORT1   3
#define PI_PORT0    4
#define PI_PORT1    5
#define CFG_PORT0   6
#define CFG_PORT1   7

#define PIN_INT 7   //GPIO.7 in wiringPi encode

int i2c_fd = 0;
char p0_val = 0x00;
char p1_val = 0xff;
unsigned char int_flag = 0;
unsigned char res = 0;
unsigned int t = 0;
/****************************************************
 * name：WriteRawRC   
 * describe：write RC522 register  
 * input ：ucAddress， ucValue
 */
void Write_reg( unsigned char reg_addr, unsigned char value )
{  
    wiringPiI2CWriteReg8(i2c_fd, reg_addr&0x07, value );
}
/***************************************************************
 * name：ReadRawRC 
 * read current value from the register
 */
unsigned char Read_reg ( unsigned char reg_addr )
{
    return wiringPiI2CReadReg8(i2c_fd, reg_addr&0x07);
}

void Read_pin_state(void)
{
    if(int_flag == 0)
    {
       int_flag = 1;    
    }
}

void Cat9555_Init(void)
{
    wiringPiSetup(); //init wiringpi lib
    i2c_fd = wiringPiI2CSetup(DEV_ADRR);
    printf("dev_addr:%d\r\n", i2c_fd);
    pinMode(PIN_INT,INPUT);
    pullUpDnControl(PIN_INT,PUD_UP);
    wiringPiISR(PIN_INT,INT_EDGE_FALLING, &Read_pin_state);
}


int main(void)
{
    Cat9555_Init();
    Write_reg(CFG_PORT0, 0x00);//set the port 0 as output
    Write_reg(CFG_PORT1, 0xFF);//set the port 1 as intput
    printf("cfg_port0:%x \r\n", Read_reg(CFG_PORT0));//read the configuration port 0 register
    printf("cfg_port1:%x \r\n", Read_reg(CFG_PORT1));//read the configuration port 1 register
    Write_reg(PI_PORT1, 0x00);
    while(1)
    {
        delay(20);
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
