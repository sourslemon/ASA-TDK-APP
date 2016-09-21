#include "ASA_Lib.h"

int INT4_COUNT = 0;
int temp = 0;

void INT_set(char INT_num,char mode);

int main(void)
{

	ASA_M128_set();
	printf("START!!\n");
	// INT4_vect_init();
	INT_set(4,3);
	printf("DDRB  = %d\n", DDRB);
	printf("EICRA = %d\n", EICRA);
	printf("EICRB = %d\n", EICRB);
	printf("EIMSK = %d\n", EIMSK);
	sei();
	while (1) {
		asm("nop");
		printf("INT4_COUNT = %d\n", INT4_COUNT);
		if ( temp < INT4_COUNT) {
			printf("INT4_COUNT = %d\n", INT4_COUNT);
			temp = INT4_COUNT;
		}
		asm("nop");
		// printf("PINB = %d\n", PINB);

		// printf("%d\n", INT4_COUNT);

	}
}
void INT_set(char INT_num,char mode) {
	DDRB |= 1<<(INT_num);
	if (INT_num<4) {
		EICRA |= (mode)<<(INT_num*2);
	}else{
		EICRB |= (mode)<<((INT_num - 4)*2);
	}
	EIMSK |= 1<<INT_num;
}

void INT4_vect_init(){
	// EICRA=0x00 /*設定外部中斷3:0偵知方式，非外部中斷不需要，*/
	DDRB = 0XFF;
	EICRB = 0x03;
	// EICRB |= (1<<ISC41) && (1<<ISC40); /*設定中斷7:4偵知方式*/
	EIMSK |= (1<<INT4);  /*設定中斷致能*/

	sei(); /*設定所有中斷均致能*/
}

ISR(INT4_vect)
{
	asm("nop");
	INT4_COUNT++;
}

char ASA_PWM00_set(char ASA_ID, char LSByte, char Mask, char shift, char Data);
char ASA_PWM00_put(char ASA_ID, char LSByte, char Bytes, void *Data_p);


// 85 ms 最敏感
// 85*22 = 1870
