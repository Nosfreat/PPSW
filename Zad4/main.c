#include "LED.h"
#include "TIMER_INTERRUPTS.h"
#include "KEYBOARD.h"
#include <LPC21xx.H>
#include "SERVO.h"
#include "TIMER.h"



int main (){
	LedInit();
	KeyboardInit();	
	ServoInit(5);
	while(1){
		switch(eReadButton()){
			case BUTTON_0:
				ServoCallib();
				break;			
			case BUTTON_1:
				ServoGoTo(50);
				break;
			case BUTTON_2:
				ServoGoTo(100);
				break;
			default:
				break;
		}
	}
}
