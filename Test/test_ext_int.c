// 17.05.15 by Syue	Ming-You
// ecoded in utf-8
// 光遮斷器訊號經過比較器
// 以PE4外部中斷並做記數動作
#include "..\TDK_Lib\TDK_external.h"
#include "..\TDK_Lib\ASA_Lib.h"

int COUNT=0;

int main(void)
{
    ASA_M128_set();
    printf("EXT INT test by Ming-You 17.05.15\n");
    sei();
    EXT_INT_set(4,3);
    while (1) {
    printf("%d\n",COUNT);
    }
}
ISR(INT4_vect){
    COUNT++;
}
