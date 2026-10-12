#include "kernel.h"
#include "config.h"
#include "core.h"

int fadeAmount = 5;
int brightness_1 = 0;
int brightness_2 = 255;
int pins[] = {RED_PIN1, RED_PIN2, GREEN_PIN1, GREEN_PIN2};
int buttons[] = {BUT1, BUT2};

void initializeGame(){
  Serial.begin(115200);
  for(int i = 0; i< N_PLAYERS*2; i++){
    pinMode(pins[i], OUTPUT);
  }
  for(int i = 0; i<N_PLAYERS; i++){
    pinMode(buttons[i], INPUT);
  }
}

void startingPhase(){
  analogWrite(RED_PIN1, brightness_1);
  analogWrite(RED_PIN2, brightness_2);
  brightness_1 = brightness_1 + fadeAmount;
  brightness_2 = brightness_2 - fadeAmount;
  if(brightness_1 == 255 || brightness_1 == 0){
    fadeAmount = -fadeAmount;
  }
}

void gamePhase(){
  
}

void endPhase(){
  
}
