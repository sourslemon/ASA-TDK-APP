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
#include "ASA_Lib.h"

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

void main()
{
    ASA_M128_set();
	printf("Motor test by LiYu 16.9.25\n");

    //Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=3499;  //fPWM=50Hz (Period = 20ms Standard).

	DDRB|=(1<<PB5)|(1<<PB6)|(1<<PB7);   //PWM Pins as Out

	while(1)
	{
		printf("Input OCR1:");
        scanf("%d", &OCR1A);
	}
}
