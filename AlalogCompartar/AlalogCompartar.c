#include "ASA_Lib.h"

int INT4_COUNT = 0;
int temp = 0;

void AC_init();

int main(void)
{
	char status = 0, new_status=0;
	ASA_M128_set();
	printf("AlalogCompartar test by LiYu\n");
	AC_init();
	while (1) {
		asm("nop");
		new_status = (ACSR>>5) && 1;
		if (new_status != status) {
			asm("nop");
			status = new_status;
			printf("Changed! status = %d\n", status);
		}
		// printf("status = %d\n", status);
		// status = (ACSR>>5) && 1;
		asm("nop");
	}
}
void AC_init() {
	SFIOR = 1 << ACME;
	ACSR  = (1<<ACIE) || (1<<ACIS1) || (1<<ACIS0);
}
/**
 *STEP1.SFIOR (Special Function IO Register) set
 *enable ACME (Analog Comparator Multiplexer Enable)
 *STEP2. ACSR (Analog Comparator Control and Status Register) set
 *
 *
 *
 */
