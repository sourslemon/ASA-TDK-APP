#include "..\TDK_Lib\TDK_Lib.h"

int main(void)
{
	ASA_M128_set();
	printf("Motor test by LiYu 2017.05.14\n");

	/*=== init ===========================================*/
	motor_set(MOTOR_RIGHT,0,DISABLE);
	motor_set(MOTOR_LEFT, 0,DISABLE);
	motor_set(MOTOR_Y, 0,DISABLE);
	motor_set(MOTOR_RIGHT,1,0);
	motor_set(MOTOR_LEFT, 1,0);
	motor_set(MOTOR_Y,1,0);
	/*=== init ===========================================*/
	sei();
    int input;
    uint8_t id;
	uint16_t speed; //0~511

	while (1) {
		printf("\ninput motor id:");
		scanf("%d",&input);
        id = input;
        printf("\ninput motor speed:");
        scanf("%d",&input);
        speed = input;
        motor_set(id,1,speed);
	}
    return 0;
}
