#include "..\TDK_Lib\ASA_Lib.h"

char error_X = 0,error_Y = 0,error_Z = 0;
int X = 0,Y = 0,Z = 0;

int main(void)
{		
    ASA_M128_set();
    spi_init_master();
            while(1)
	{
           error_X  = ASA_JS00_get(1,100,2,&X);  //�۶s�q�D���' ��1��
	//_delay_ms(100);
	error_Y  = ASA_JS00_get(1,102,2,&Y);  //�۶s�q�D���' ��1��
	//_delay_ms(100);
	error_Z  = ASA_JS00_get(1,104,2,&Z);   //�۶s�q�D���' ��1��
	//_delay_ms(100);
   
           printf("error_X=%d  error_Y=%d   error_Z=%d ",error_X,error_Y,error_Z);  //���error��
           printf("X=%5d  Y=%5d  Z=%2d\n",X,Y,Z);  //���XYZ��
 	_delay_ms(100);
	}

	return 0;
}