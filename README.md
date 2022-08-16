CAT9555-IO-Expansion-Module from seengreat:www.seengreat.com
 =======================================
# Instructions
## 1.1、Overview
This product provides 16−bit parallel input/output port expansion for I2C and SMBus compatible applications. These I/O expanders provide a simple solution in applications where additional I/Os are needed: sensors, power switches, LEDs, buttons, and fans.<br>
The communication interface of this product is I2C, and the maximum communication rate is 400KHz. The board also leads out a PH2.0 5Pin socket, a 2.54 pitch pin header and all IO expansion ports. We provide demo codes based on Raspberry Pi, Arduino UNO, and STM32, which are convenient for users to use on different platforms.<br>
## 1.2、Parameters
|DIMENTIONS	|45mm(Length)*25mm(Width)|
|----------------------|--------------------------------|
|NUMBER OF I/O PORTS	|16|
|CONTROL CHIP	|CAT9555|
|SIGNAL INTERFACE	I2C|
|SUPPLY VOLTAGE	|3.3V/5V|

# Usage
## 2.1、Instructions of Hardware Interface Configuration
### 2.1.1、Wiring Instructions of Raspberry Pi
The demo codes in the Raspberry Pi motherboard adopts the pin definitions encoded by wiringPi, and the definition of the wiring with the Raspberry Pi motherboard is shown in the following table:<br>

|Connector	|Pin Function	|BCM Number	|WiringPi Number	|BOARD Number|
|----------------------|-----------------------|----------------------|----------------------|------------------|
|VCC	|3.3V	|3.3V	|3.3V	|1|
|GND	|GND	|GND	|GND	|6|
|SDA	|SDA.1	|2	|8	|3|
|SCL	|SCL.1	|3	|9	|5|
|INT	|GPIO.7	|4	|7	|7|

 Table 2-1 Pin Definitions of the Wiring between the Module and Raspberry Pi<br>
The Raspberry Pi is connected to the module, and the wiring diagram is shown in Figure 2-1.<br>
![1.jpg](https://github.com/seengreat/CAT9555-IO-Expansion-Module/blob/main/pic/pic1.png)<br>
Figure 2-1 The Diagram of the Wiring between the Module and Raspberry Pi<br>
### 2.1.2、Wiring Instructions of Arduino
The wiring between the module and Arduino pins is shown in the following table:<br>
|CAT9555 IO Expansion Module	|Arduino UNO R3|
|---------------------------------------------|------------------|
|VCC	|3.3V|
|GND	|GND|
|SDA	|SDA|
|SCL	|SCL|
|INT	|D2|

Table 2-2 Pin Definitions of the Wiring between the Module and Arduino UNO R3<br>
![2.jpg](https://github.com/seengreat/CAT9555-IO-Expansion-Module/blob/main/pic/pic2.png)<br>
Figure 2-2 The Diagram of the Wiring between the Module and Arduino<br>
### 2.1.3、Wiring Instructions of STM32
The wiring between the module and STM32F103 pins is shown in the following table:<br>
|CAT9555 IO Expansion Module	|STM32F103|
|---------------------------------------------|-------------|
|VCC	|3.3V|
|GND	|GND|
|SDA	|PB10|
|SCL	|PB11|
|INT	|PB3|

Table 2-3 Pin Definitions of the Wiring between the Module and STM32F103<br>
### 2.1.4、Device Addressing
After the bus Master sends a START condition, a slave address byte is required to enable the CAT9555 for a read or write operation. The four most significant bits of the slave address are fixed as binary 0100 (Figure 2-3). The CAT9555 uses the next three bits as address bits. The address bits A2, A1 and A0 are used to select which device is accessed from maximum eight devices on the same bus. These bits must compare to their hardwired input pins. <br>
The 8th bit following the 7−bit slave address is the R/W bit that specifies whether a read or write operation is to be performed. When this bit is set to “1”, a read operation is initiated, and when set to “0”, a write operation is selected. Following the START condition and the slave address byte, the CAT9555 monitors the bus and responds with an acknowledge (on the SDA line) when its address matches the transmitted slave address. The CAT9555 then performs a read or a write operation depending on the state of the R/W bit.<br>
![3.jpg](https://github.com/seengreat/CAT9555-IO-Expansion-Module/blob/main/pic/pic3.png)<br>

Figure 2-3. CAT9555 Slave Address<br>
When the on-board toggle switch is turned to the "ON" state, the address state on this bit is low level ("0"), and when it is turned to the other side, it is high level ("1"),The status settings of A2 A1 A0 are shown in the following table:<br>
|I2C Address line	|toggle switch “ON” state	|toggle switch “OFF” state|
|----------------------|----------------------------------|------------------------------|
|A0	|0	|1|
|A1	|0	|1|
|A2	|0	|1|

## 2.2、Usage of Demo Codes
### 2.2.1、Usage of Demo Codes for Raspberry Pi
_1、wiringpi Libraries Installation_
   sudo apt-get install wiringpi<br>
   wget https://project-downloads.drogon.net/wiringpi-latest.deb  # Raspberry Pi 4B version upgrade<br>
   sudo dpkg -i wiringpi-latest.deb<br>
   gpio -v # If version 2.52 appears, it means that the installation has been successful<br>
_2、I2C Configuration of Raspberry Pi_
Start the system configuration of Raspberry Pi<br>
sudo raspi-config<br>
Enable SPI Interface<br>
Interfacing Options -> I2C -> Yes<br>
sudo reboot<br>
Check the enabled SPI devices:<br>
ls /dev/i2c*   # at this time it will print：“/dev/i2c-1”<br>
Install the I2C libraries<br>
sudo apt install i2c-tools <br>
Install python's smbus:<br>
sudo apt install python-smbus <br>
After wiring the module according to the wiring definitions in Table 2-1 and Figure 2-1, use the following commands to test the device address mounted on the I2C bus:<br>
sudo i2cdetect -y -a 1<br>
_3、Demo Codes Running_
C Demo Codes：<br>
Access the directory of demo codes:<br>
cd /home/pi/cat9555/c<br>
sudo make clean<br>
sudo make<br>
sudo ./main<br>
Python Demo Codes:<br>
Access the directory of demo codes:<br>
cd /home/pi/cat9555/python<br>
python3 cat9555.py<br>
In the demo codes, the P0 port is configured as an output, the P1 port is configured as an input, and the P0 port reverses the IO port state every 1 second. when the IO state input by the P1 port changes, the serial port will output the current state of the P1 port.<br>
### 2.2.2、Usage of Demo Codes for Arduino UNO R3
After installing the Ariduino IDE software, wire the module according to the wiring definitions in Table 2-2 and Figure 2-2, double-click to access the cat9555.ino file in the demo codes, click the "Verify" and "Upload" buttons successively, and then access " "Tools" -> "Serial Monitor" to check the input status of the P1 port.<br>
In the demo codes, the P0 port is configured as an output, the P1 port is configured as an input and the P0 port reverses the IO port state every 1 second. When the IO state input by the P1 port changes, the serial port will output the current state of the P1 port.<br>
### 2.2.3、Usage of Demo Codes for STM32
This demo codes are based on the STM32F103CBT6 single-chip microcomputer. Wire the module according to the wiring definitions in Table 2-3. If you need to check the input status of the P1 port, you need to connect the UART1 port (3.3V TTL level) of the STM32 to the PC. PA9 is transmissed the pins for data, and PA10 is used to receive the pins for data.<br>
The demo codes are written based on Keil uVsion5, and the user needs to install the software in advance. After wiring, double-click to access the project file main.uvprojx in the demo codes/STM32/USER/ path, and then click the "Build" button to compile. After the compilation is successful, click the "LOAD" button to download the compiled executable file to STM32. The download method and the corresponding downloader are configured by the user.<br>
The running situation of the demo codes is the same as that of Raspberry Pi and Arduino UNO. The P0 port reverses the IO port status every 1 second, and the P1 port is used as the input port.<br>

__Thank you for choosing the products of Shengui Technology Co.,Ltd. For more details about this product, please visit:
www.seengreat.com__

