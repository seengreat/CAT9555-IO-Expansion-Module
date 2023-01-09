#ifndef __CAT9555_H
#define	__CAT9555_H	
#include "sys.h"

#define I2C_ADDR    0x20<<1

//CAT9555 regsiter
#define IN_PORT0    0
#define IN_PORT1    1
#define OUT_PORT0   2
#define OUT_PORT1   3
#define PI_PORT0    4
#define PI_PORT1    5
#define CFG_PORT0   6
#define CFG_PORT1   7

void CAT9555_WR_Reg(u8 RCsla,u8 addr,u8 val);
unsigned char CAT9555_RD_Reg(u8 RCsla,u8 addr);
unsigned char Read_reg(unsigned char Address);
void Write_reg(unsigned char Address, unsigned char value);

#endif

