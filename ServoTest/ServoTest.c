#include "ASA_Lib.h"

void main()
{
    ASA_M128_set();
	printf("Motor test by LiYu 16.9.25\n");

    TIMER1_init();


	DDRB|=(1<<PB5)|(1<<PB6)|(1<<PB7);   //PWM Pins as Out

	while(1)
	{
        printf("\nInput OCR1A:");
        scanf("%d", &OCR1A);
        printf("\nInput OCR1B:");
        scanf("%d", &OCR1B);
        //80~340 分180等分
	}
}
void TIMER1_init(){
    //Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM (enable OCR1A,OCR1B)
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(0<<CS10); //PRESCALER=8 MODE 14(FAST PWM)

	ICR1=27992;  //fPWM=50Hz (Period = 20ms Standard).
    //PRESCALER=8 ICR1=27992
    //PRESCALER=64 ICR1=3499
}
void servo_set(uint8_t id,uint8_t target_angle){
    // 0.00052643 (ms/per_val)
    // min = 640  (0.3369 ms) 0 degree
    // max = 2720 (1.9434 ms) ? degree TODO:測量此角度
    // TODO 觀察 OCR-角度 是否呈現線性關係
    // TODO 是否增加低轉速模式 (每段時間增加定植，直到達到目標值

    //(2720-640)/180 = 11.55 (degree/per_arget_data)
    uint16_t target_data = (float)target_angle * 11.55;
    if (id == 0) {
        TCCR1A = target_data;
    } else if (id == 1) {
        TCCR1B = target_data;
    } else {
        return 1;
    }

    return 0;
    // return 0:沒問題, 1:wrong ID, 2:wrong mode, 3:wrong data
}
