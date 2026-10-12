#include "config.h"
#include "kernel.h"
#include "core.h"

#include <TimerOne.h>

int state;
unsigned long changeStateTime;
unsigned long currentTimeInState;

void wakeUp(){
	changeState(START_PHASE);
	startingPhase();
}

void sleeping(){
	int buttons[] = {BUT1, BUT2};
	for(int i = 0; i < N_PLAYERS; i++){
		pinMode(buttons[i], INPUT);
		attachInterrupt(digitalPinToInterrupt(buttons[i]), wakeUp, RISING);
	}
	logMsg("Going to sleep... zzz");
	changeState(SLEEP);
}

void initKernel(){
	Timer1.disablePwm(RED_PIN1);
	Timer1.disablePwm(RED_PIN2);
	changeState(START_PHASE);
	currentTimeInState = 0;
}

void updateStateTime(){
	currentTimeInState = millis() - changeStateTime;
}
void changeState(int new_state){
	state = new_state;
	if(new_state == START_PHASE){
		sleepTimer();
	}else{
		stopTimer();
	}
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

void sleepTimer(){
	//10 seconds timer
	logMsg("Starting Sleep Timer");
	Timer1.initialize(65000);
	Timer1.attachInterrupt(sleeping);
}

void stopTimer(){
	Timer1.stop();
}

void logMsg(const String& msg){
	#ifdef __DEBUG__
	Serial.println(msg);
	#endif
}