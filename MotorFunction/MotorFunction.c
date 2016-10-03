#include "ASA_Lib.h"

#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

#define PWM_1_ASA_ID 1
#define PWM_2_ASA_ID 2
#define RIGHT_MOTOR_ID 0
#define LEFT_MOTOR_ID  1
#define Z_MOTOR_ID 2
#define Y_MOTOR_ID 3

#define DISABLE 0
#define ENABLE  1

void TIMER2_OVF_init();
void TIMER2_OVF_reg (void (*function)(void));
void (*TIMER2_OVF_fun)()=0;

void INT_set(char INT_num,char mode);
void PORTE_init();

uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data);
uint8_t go_step(uint16_t steps);
void motor_count_steps();


uint16_t COUNT=0;
uint16_t NEW_COUNT=0;
uint16_t TARGET_STEPS=0;

int main(void)
{
	ASA_M128_set();
	printf("Motor test by LiYu 16.9.25\n");

	int check = 0;
	uint16_t pwm_data=0;
	PORTE_init();

	check = motor_set(RIGHT_MOTOR_ID,0,ENABLE);
	printf("%d\n", check);
	check = motor_set(LEFT_MOTOR_ID, 0,ENABLE);
	printf("%d\n", check);
	check = motor_set(RIGHT_MOTOR_ID,1,0);
	printf("%d\n", check);
	check = motor_set(LEFT_MOTOR_ID, 1,0);
	printf("%d\n", check);

	int id,mode,data;
	while (1) {
		printf("\nID:");
		scanf("%d", &id);
		printf("\nMode:");
		scanf("%d", &mode);
		printf("\nData:");
		scanf("%d", &data);
		check = motor_set(id, mode,data);
		printf("\ncheck=%d\n", check);
	}

	// check = ASA_PWM00_set(PWM_1_ASA_ID,SET_START_LSBYTE,0x01,0,1);	//set PWM M1 enable
	// printf("debug2 = %d,%d,%d,%d\n",PWM_1_ASA_ID,SET_START_LSBYTE,0x01,0,1);
	// printf("c1=%d\n",check);									//check point1
	// check = ASA_PWM00_put(PWM_1_ASA_ID,PUT_START_LSBYTE,2,&pwm_data);	//put PWM M1 STOP
	// printf("debug2 = %d,%d,%d,%d\n",PWM_1_ASA_ID,PUT_START_LSBYTE,2,pwm_data);
	// printf("c2=%d\n",check);

	INT_set(4,3);
	// while (1) {
	// 	// printf("%d\n", COUNT);
	// }
}
void INT_set(char INT_num, char mode) {
	// mode 0:low level trigger
	// mode 1:logic change trigger
	// mode 2:falling edge
	// mode 3:rising trigger
	if (INT_num<4) {
		// EICRA |= (mode)<<(INT_num*2);
		return;
	}else{
		DDRE  &= ~(1<<INT_num);
		PORTE |= (1<<INT_num);
		EICRB |= (mode)<<((INT_num - 4)*2);
	}
	EIMSK |= (1<<INT_num);
}
void PORTE_init() { //initialize PORTE 4~7 bits
	DDRE  = 0xF0;
	PORTE = 0xF0;
}
ISR(INT4_vect){
	COUNT++;
}


uint8_t motor_set(uint8_t motor_ID, uint8_t mode, uint16_t data) {
	uint8_t pwm_asa_id = 0;
	uint8_t pwm_channel = 0;
	uint8_t check = 0;
	static enable_status[2]={0};

	if (motor_ID == 0 || motor_ID == 1 ) {
		pwm_asa_id  = PWM_1_ASA_ID;
		pwm_channel = motor_ID+1;
	} else if (motor_ID == 2 || motor_ID == 3) {
		pwm_asa_id  = PWM_2_ASA_ID;
		pwm_channel = motor_ID-1;
	} else {
		return 1;
	}
	// TODO: 測量最低驅動波寬比為多少

	// mode 0:開關PWM, 1:正轉, 2:反轉
	switch (mode) {
		case 0:
			if (data!=0 && data!=1) { return 3; }
			if (data==0) {
				enable_status[pwm_asa_id-1] &= ~(1<<(pwm_channel-1));
			} else if (data==1) {
				enable_status[pwm_asa_id-1] |= 1<<(pwm_channel-1);
			}
			data = enable_status;
			check = ASA_PWM00_set(pwm_asa_id, SET_START_LSBYTE,3,0, data);
			// printf("%d\n", enable_status[pwm_asa_id-1]);
			// printf("debug1 = %d,%d,%d,%d,%d\n",pwm_asa_id,SET_START_LSBYTE,(1<<(pwm_channel-1)),pwm_channel-1,data);
			// check = ASA_PWM00_set(pwm_asa_id, SET_START_LSBYTE, (1<<(pwm_channel-1)), pwm_channel-1, data);
			if (check!=0) { return 10+check; }
			break;
		case 1:
			if (data>500) { return 3; }
			data = 500-data;
			check = ASA_PWM00_put(pwm_asa_id, (PUT_START_LSBYTE + pwm_channel*2-2), 2, &data);
			// printf("debug2 = %d,%d,%d,%d\n",pwm_asa_id,(PUT_START_LSBYTE + pwm_channel*2 - 2),2,data);
			if (check!=0) { return 10+check; }
			break;
		case 2:
			if (data>500) { return 3; }
			data = data+500;
			check = ASA_PWM00_put(pwm_asa_id, (PUT_START_LSBYTE + pwm_channel*2-2), 2, &data);
			// printf("debug3 = %d,%d,%d,%d\n",pwm_asa_id,(PUT_START_LSBYTE + pwm_channel*2 - 2),2,data);
			if (check!=0) { return 10+check; }
			break;
		default:
			return 2;
	}

	return 0;
	// return 0:沒問題, 1:wrong ID, 2:wrong mode, 3:wrong data, 1x:ASA_PWM錯誤 X為PWM錯誤代碼
}

uint8_t go_step(uint16_t steps){
	COUNT = 0;
	INT_set(4,3);
	TARGET_STEPS = steps;
	TIMER2_OVF_reg(motor_count_steps);
	motor_set(RIGHT_MOTOR_ID,0,ENABLE);
	motor_set(LEFT_MOTOR_ID, 0,ENABLE);
	return 0;

}
void motor_count_steps(){
	if (COUNT >= TARGET_STEPS) {
		TIMER2_OVF_reg(NULL);
	}
	motor_set(RIGHT_MOTOR_ID,0,DISABLE);
	motor_set(LEFT_MOTOR_ID, 0,DISABLE);
	return ;
}

/*--------------------------interrupt function set--------------------------*/
ISR(TIMER2_OVF_vect){
	TIMER2_OVF_fun();
}
void TIMER2_OVF_init(){
    TCCR2 |= 1;	// set up timer with prescaler = 2
    TCNT2  = 0;	// initialize counter
    TIMSK |=(1 << TOIE2);// enable overflow interrupt
    // sei();// enable global interrupts
}
void TIMER2_OVF_reg (void (*function)(void)){
	TIMER2_OVF_fun=function;
}
