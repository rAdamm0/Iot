#include "kernel.h"
#include "config.h"
#include "core.h"

int pins[] = {RED_PIN1, RED_PIN2, GREEN_PIN1, GREEN_PIN2};
int buttons[] = {BUT1, BUT2};

void initializeGame(){
  for(int i = 0; i< N_PLAYERS*2; i++){
    pinMode(pins[i], OUTPUT);
  }
  for(int i = 0; i<N_PLAYERS; i++){
    pinMode(buttons[i], OUTPUT);
  }
}

void startingPhase(){
  
}

void gamePhase(){
  
}

void endPhase(){
  
}
