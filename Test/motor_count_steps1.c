#include "..\TDK_Lib\TDK_Lib.h"

int main(void)
{
	ASA_M128_set();
	printf("Motor test by LiYu 2017.05.14\n");

	/*=== init ===========================================*/
	motor_set(MOTOR_RIGHT,0,DISABLE);
	motor_set(MOTOR_LEFT, 0,DISABLE);
	motor_set(MOTOR_Y, 0,DISABLE);
	motor_set(MOTOR_RIGHT,1,200);
	motor_set(MOTOR_LEFT, 1,200);
	motor_set(MOTOR_Y,1,200);
	/*=== init ===========================================*/
	sei();
	uint16_t target_steps;

	while (1) {
		printf("\ninput target_steps:");
		scanf("%d",&target_steps);
		motor_go_steps(MOTOR_RIGHT,target_steps);
	}
}
