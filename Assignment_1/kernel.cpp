#include "config.h"
#include "kernel.h"
#include "core.h"

#include <TimerOne.h>
#include <avr/sleep.h>

int state;
unsigned long changeStateTime;
unsigned long currentTimeInState;
volatile int sleepCounter = 0;

void wakeUp(){
}

void sleeping(){
	int buttons[] = {BUT1, BUT2};
	for(int i = 0; i < N_PLAYERS; i++){
		pinMode(buttons[i], INPUT);
		attachInterrupt(digitalPinToInterrupt(buttons[i]), wakeUp, CHANGE);
	}
	changeState(SLEEP);
	logMsg("Going to sleep... zzz");
	Serial.flush();
	delay(1000);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
	changeState(START_PHASE);
	logMsg("Wake UP!");
}

void sleepCounterFun(){
	sleepCounter = sleepCounter + 1;
}

void initKernel(){
	changeState(START_PHASE);
	currentTimeInState = 0;
}

void updateStateTime(){
	currentTimeInState = millis() - changeStateTime;
	logMsg(String(sleepCounter));
	if(sleepCounter == SLEEP_TIMER){
		sleeping();
	}
}
void changeState(int new_state){
	if(state == new_state){
		return;
	}
	state = new_state;
	changeStateTime = millis();
	if(state == START_PHASE){
		sleepCounter = 0;
		Timer1.initialize(1000000);
		Timer1.attachInterrupt(sleepCounterFun);
	}else{
		Timer1.stop();
	}
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