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

	uint8_t PWM_ASA_ID = 1;
	unsigned int pwm_data = 500;
	uint8_t check = 0;
	uint8_t target_cycle = 0;
	uint8_t teeth = 23; //原24 減掉鑽孔處偵測為23

	PORTE_init();
	INT_set(4,3);

	sei();

	check = ASA_PWM00_set(PWM_ASA_ID,SET_START_LSBYTE,0x01,0,1);	//set PWM M1 enable
	printf("c1=%d\n",check);										//check point1
	check = ASA_PWM00_put(PWM_ASA_ID,PUT_START_LSBYTE,2,&pwm_data);	//put PWM M1 STOP
	printf("c2=%d\n",check);										//check point1

	while (1) {
		printf("\ninput target_cycle:");
		scanf("%d",&target_cycle);

		pwm_data = 0;
		ASA_PWM00_put(PWM_ASA_ID,0,2,&pwm_data);

		COUNT = 0;
		while( COUNT <= target_cycle * teeth ){
			//do something here ,otherwise get a bug that no break out while
			printf(" ");
		}

		printf("\nEND-------");
		pwm_data = 500;
		ASA_PWM00_put(PWM_ASA_ID,0,2,&pwm_data);
	}

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
	if (motor_ID == 0 || motor_ID == 1 ) {
		pwm_asa_id  = PWM_1_ASA_ID;
		pwm_channel = motor_ID;
	} else if (motor_ID == 2 || motor_ID == 3) {
		pwm_asa_id  = PWM_2_ASA_ID;
		pwm_channel = motor_ID-2;
	} else {
		return 1;
	}

	// mode 0:開關PWM, 1:正轉, 2:反轉

	switch (mode) {
		case 0:
			if (data!=0 || data!=1) { return 3; }
			check = ASA_PWM00_set(pwm_asa_id, SET_START_LSBYTE, (1<<pwm_channel), pwm_channel, data);
			if (check!=0) { return 10+check; }
			break;
		case 1:
			if (data>500) { return 3; }
			check = ASA_PWM00_put(pwm_asa_id, (PUT_START_LSBYTE + pwm_channel*2), 2, &data);
			if (check!=0) { return 10+check; }
			break;
		case 2:
			if (data>500) { return 3; }
			data = data+500;
			check = ASA_PWM00_put(pwm_asa_id, (PUT_START_LSBYTE + pwm_channel*2), 2, &data);
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
	return 0;
}

/*--------------------------interrupt function set--------------------------*/
ISR(TIMER2_OVF_vect){
	TIMER2_OVF_fun();
}
void TIMER2_OVF_init(){
    TCCR2 |= 1;	// set up timer with prescaler = 2
    TCNT2  = 0;	// initialize counter
    TIMSK |=(1 << TOIE2);// enable overflow interrupt
    sei();// enable global interrupts
}
void TIMER2_OVF_reg (void (*function)(void)){
	TIMER2_OVF_fun=function;
}
