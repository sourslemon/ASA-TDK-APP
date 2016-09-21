#include "ASA_Lib.h"

void INT_set(char INT_num,char mode);

int main(void)
{

	ASA_M128_set();
	printf("START!!\n");

	INT_set(4,3);
	sei();
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
ISR(INT4_vect){
	
}
