#include <LPC21xx.H>
#include "TIMER.h"

#define TIMER0ENABLE_bm (0x1)
#define TIMER0RESET_bm (0x2)
#define TIMER_INT_M0_bm (0x1)
#define TIMER_RESET_M0_bm (0x2)
#define INT_FLAG_bm (0x1)

void InitTimer(void){
	T0TCR = T0TCR | TIMER0ENABLE_bm;
}



void WaitOnTimer( unsigned int uiTime){
	uiTime = (uiTime*15000);
	T0TCR = T0TCR | TIMER0RESET_bm ;
	T0TCR = T0TCR & ~(TIMER0RESET_bm) ;
	while(uiTime > T0TC){
	}	
}

void InitTimer0Match0(unsigned int iDelayTime){
	iDelayTime = (iDelayTime*15000);
	T0MCR = (T0MCR | TIMER_INT_M0_bm | TIMER_RESET_M0_bm);
	T0MR0 = iDelayTime;
	InitTimer();
	T0TCR = T0TCR | TIMER0RESET_bm ;
	T0TCR = T0TCR & ~(TIMER0RESET_bm) ;
}

void WaitOnTimer0Match0(void){
	while ( (T0IR & INT_FLAG_bm)==0){
	}
	T0IR = T0IR | ~(INT_FLAG_bm);	
	
}
