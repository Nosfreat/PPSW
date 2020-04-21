#include <LPC21xx.H>
#include "KEYBOARD.h"

#define BUTTON0 1<<4
#define BUTTON1 1<<6
#define BUTTON2 1<<5
#define BUTTON3 1<<7


void KeyboardInit(void){
	IO0DIR= IO0DIR & ~(BUTTON0 | BUTTON1 | BUTTON2 | BUTTON3);
}


void Delay ( int iMilisekundy ){
	unsigned int ucLicznik;
	iMilisekundy = 12000  * iMilisekundy;
	for (ucLicznik = 0 ; ucLicznik < iMilisekundy; ucLicznik ++)
	{}
	}
	

enum ButtonState eReadButton(void){
	if ((IO0PIN & BUTTON0) == 0) 
		return BUTTON_0;
	else if ((IO0PIN & BUTTON1) == 0)
		return BUTTON_1;
	else if ((IO0PIN & BUTTON2) == 0)
		return BUTTON_2;
	else if ((IO0PIN & BUTTON3) == 0)
		return BUTTON_3;
	else
		return RELASED;
}

