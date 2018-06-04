/*
 * USER_TIMER.C
 *
 *  Created on: 2013. 2. 12.
 *      Author: mcssol
 */
#include "MSP430_TIMER.h"




void Init_TimerA0_3_PWM(unsigned int PWM_period_ms)
{
	unsigned int tmp_cnt=0;
	/* LCD PORT ENABLE************************/
	P8DIR|=0x08;
	P8SEL|=0x08;//SEL TIMER_A
	/****************************************/
	tmp_cnt=(PWM_period_ms*((float)ACLK_FREQ/(float)1000ul));

	TA0CTL=TASSEL_1+TACLR+MC_1;

	TA0CCR0=tmp_cnt;

	TA0CCR3=tmp_cnt>>1;
	TA0CCTL3=OUTMOD_3;
}

/*
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
		P1OUT ^= 0x02;                            // Toggle P1.0
}
*/
