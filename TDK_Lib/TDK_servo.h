#ifndef TDK_servo_H_
#define  TDK_servo_H_

#include "ASA_Lib.h"

/*=== Servo Funtion Define ===============================*/
#define SERVO_GRIPPING 0
#define SERVO_ROTATING 1
/*========================================================*/

/*=== Timer3 function ====================================*/
void TIMER3_init();
/*========================================================*/

/*=== Servo funcion ======================================*/
void servo_init();
uint8_t servo_set(uint8_t id,uint8_t target_angle);
// TODO 是否增加低轉速模式 (每段時間增加定值，直到達到目標值 )
/*========================================================*/

#endif
