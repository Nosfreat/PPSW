#include "KEYBOARD.h"
#include <LPC21xx.H>
#include "LED.h"
#include "TIMER_INTERRUPTS.h"

#define DETECTOR_bm (1<<10)

void DetectorInit(){
	IO0DIR = IO0DIR & ~(DETECTOR_bm);			//ustawienie bitu jako we
}

/*
///////detektor na czujniku////////////
enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector(){
	if ((IO0PIN & DETECTOR_bm) == 0){
		return INACTIVE;
	}
	else {
		return ACTIVE;
	}
}
////////////////////////////////////////
*/	
//////detektor na przycisku 3/////////
#define BUTTON3 1<<7
enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector(){
	if ((IO0PIN & BUTTON3) == 0){
		return ACTIVE;
	}
	else {
		return INACTIVE;
	}
}
///////////////////////////////////////
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

struct Servo sServo;	

void Servo (){
	switch (sServo.eState){
		case CALLIB: 
			if(eReadDetector()==INACTIVE){
				LedStepLeft();
			}
			else{
				sServo.eState = IDLE;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;				
			}	
			break;
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRESS;
			}
			else{
				sServo.eState = IDLE;
			}
			break;
		case IN_PROGRESS: 
			if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRESS;
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
				sServo.eState = IN_PROGRESS;
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else{
				sServo.eState = IDLE;
			}
			break;
		default:
			break;
			break;
			}
}


void ServoCallib(void){

	sServo.eState = CALLIB;
	while(eReadDetector()==INACTIVE){};
}


void ServoInit(unsigned int uiServoFreq){
	LedInit();
	DetectorInit();
	ServoCallib();
	Timer0Interrupts_Init(1000000/uiServoFreq, &Servo);
}

void ServoGoTo(unsigned int uiPosition){
	sServo.eState = IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
}
