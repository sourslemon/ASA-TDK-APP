/******************************************************************************

Program to demonstrate the use servo motors with AVR Microcontrollers.

For More Details Visit: http://www.eXtremeElectronics.co.in

Copyright (c) 2008-2010
eXtreme Electronics, India

Servo Motor: Futaba s3003
Servo Control PIN (white): To OC1A PIN
Crystal: 16MHz
LOW Fuse: 0xFF
HIGH Fuse: 0xC9

Compiler:avr-gcc toolchain
Project Manager/IDE: AVR Studio

                                     NOTICE
                           --------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR

HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com

*******************************************************************************/
#include <avr/io.h>

#include <util/delay.h>

//Simple Wait Function
void Wait()
{
   uint8_t i;
   for(i=0;i<50;i++)
   {
      _delay_loop_2(0);
      _delay_loop_2(0);
      _delay_loop_2(0);
   }

}

int main()
{
	//setting PWM-Ports as output
	DDRB|=(1<<PB7)|(1<<PB6)|(1<<PB5);
	DDRE|=(1<<PE3);
	// PWM,Phase correct,8-Bit mode
	TCCR1A|=(1<<WGM10);
	TCCR3A|=(1<<WGM30);
	//no-inverting PWM
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<COM1C1);
	TCCR3A|=(1<<COM3A1);
	// Timer running on MCU clock/8
	TCCR1B|=(1<<CS11);
	TCCR3B|=(1<<CS31);
	//set Motor Speed
	setMotorSpeed(200,100,160,220);
	while(1);
	return 0;
}
void setMotorSpeed(unsigned char motorSpeed1, unsigned char motorSpeed2,unsigned char motorSpeed3, unsigned char motorSpeed4){
	OCR1A=motorSpeed1;
	OCR1B=motorSpeed2;
	OCR1C=motorSpeed3;
	OCR3A=motorSpeed4;
}
