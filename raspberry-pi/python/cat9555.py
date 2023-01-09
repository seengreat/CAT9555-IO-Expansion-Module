# Seengreat CAT9555 IO Expansion Module demo
# Author(s):Andy Li from Seengreat

import smbus
import time
import numpy as np
import wiringpi as wpi

#CAT9555 regsiter
IN_PORT0     = 0
IN_PORT1     = 1
OUT_PORT0    = 2
OUT_PORT1    = 3
PI_PORT0     = 4
PI_PORT1     = 5
CFG_PORT0    = 6
CFG_PORT1    = 7

#CAT9555 address
#0 1 0 0 A2 A1 A0 R/W
#R/W bit = 0 is write command
#R/W bit = 1 is read  command

PIN_INT = 7  # GPIO.7 in wiringPi encode

class CAT9555_api():
    def __init__(self):
        self.dev_addr = 0x20 #when A2=0 A1=0 A0=0 =>0010 0000
        self.i2c = smbus.SMBus(1)  # /dev/i2c-1
        self.port1 = 0xff
        wpi.wiringPiSetup()
        wpi.pinMode(PIN_INT,wpi.INPUT)
        wpi.pullUpDnControl(PIN_INT,wpi.PUD_UP)
        wpi.wiringPiISR(PIN_INT,wpi.INT_EDGE_FALLING, self.read_pin_state)
        time.sleep(1)
    def write_reg (self, reg_addr, value):
        """"write cat9555 register"""
        self.i2c.write_byte_data(self.dev_addr, reg_addr&0x07, value)
    def read_reg (self, reg_addr):
        """read current value from the register"""
        res = self.i2c.read_byte_data(self.dev_addr, reg_addr&0x07)
        return res
    def read_pin_state(self):
        time.sleep(0.02)
        res = cat9555.read_reg(IN_PORT1)
        if self.port1 != res:
            self.port1 = res
            print("port 1:",hex(self.port1))
        return 1
    
if __name__ == '__main__':
    cat9555 = CAT9555_api()
    cat9555.write_reg(CFG_PORT0, 0X00)  # set the port 0 as output
    cat9555.write_reg(CFG_PORT1, 0XFF)  # set the port 1 as intput
    res = cat9555.read_reg(CFG_PORT0)  # read the configuration port 0 register
    print("cfg_port0:", hex(res))
    res = cat9555.read_reg(CFG_PORT1)  # read the configuration port 1 register
    print("cfg_port1:", hex(res))
    cat9555.write_reg(PI_PORT1, 0X00)
    p0_val = 0x00
    while True:
        p0_val = ~p0_val
        cat9555.write_reg(OUT_PORT0, p0_val)
        time.sleep(1)
              
        
        
        
