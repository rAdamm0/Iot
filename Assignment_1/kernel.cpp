#include "kernel.h"
#include "core.h"

int state;
unsigned long changeStateTime;
unsigned long currentTimeInState;

void initKernel(){
	state = START_PHASE;
	changeStateTime = millis();
	currentTimeInState = 0;
}

void updateStateTime(){
	currentTimeInState = millis() - changeStateTime;
}
void changeState(int new_state){
	state = new_state;
	changeStateTime = millis();
}

int getCurrentState(){
	return state;
}

long getCurrentTimeInState(){
	updateStateTime();
	return currentTimeInState;
}

long getEnteredStateTime(){
	return changeStateTime;
}

bool isJustEnteredInState(){
	return millis()-changeStateTime < 100;
}

void logMsg(const String& msg){
	#ifdef __DEBUG__
	Serial.println(msg);
	#endif
}