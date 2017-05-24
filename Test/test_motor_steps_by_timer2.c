// 17.05.23 by Syue	Ming-You
// ecoded in utf-8
// 外部中斷改計時中斷
// 齒數比較精準
// 輸入圈數
// 轉的圈數=輸入圈數/2

#include "..\TDK_Lib\ASA_Lib.h"
#include "..\TDK_Lib\TDK_LIB.h"

#define SET_START_LSBYTE 200
#define PUT_START_LSBYTE 0

void PORTA_init();

int COUNT=0;
int NEW_COUNT=0;
int tmp=0,last=0;

int main(void)
{
    ASA_M128_set();
    printf("Motor test by Ming-You 16.9.25\n");
    uint8_t PWM_ASA_ID = 1;
    unsigned int pwm_data = 500;
    uint8_t check = 0;
    uint8_t target_cycle = 0;
    uint8_t teeth = 23;
    PORTA_init();
    TIMER2_init();
    sei();
    check = ASA_PWM00_set(PWM_ASA_ID,SET_START_LSBYTE,0x01,0,1); //set PWM M1 enable
    printf("c1=%d\n",check); //check point1
    check = ASA_PWM00_put(PWM_ASA_ID,PUT_START_LSBYTE,2,&pwm_data); //put PWM M1 STOP
    printf("c2=%d\n",check); //check point1
    while (1) {
        printf("\ninput target_cycle:");
        scanf("%d",&target_cycle);
        pwm_data = 0;
        ASA_PWM00_put(PWM_ASA_ID,0,2,&pwm_data);
        COUNT = 0;
        while( COUNT <= target_cycle * teeth ){
            //do something here ,otherwise get a bug that no break out while
            printf("%d",COUNT);
            printf(" ");
        }
        printf("\nEND-------");
        pwm_data = 500;
        ASA_PWM00_put(PWM_ASA_ID,0,2,&pwm_data);
    }
}

void PORTA_init() { //initialize PORTE 4~7 bits
    DDRA = 0x00;
    PORTA = 0x00;
}
ISR(TIMER2_COMP_vect){
    tmp=(PINA&1);
    if(tmp!=last)
    COUNT++;
    last=tmp;
}
