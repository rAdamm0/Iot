#include <Arduino.h>
#include "kernel.h"
#include"config.h"
#include "core.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup");
  initKernel();
  initializeGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateStateTime();
  switch(getCurrentState()){
    case START_PHASE:
      startingPhase();
      break;
    case ROUND_PHASE:
      gamePhase();
      break;
    case END_PHASE:
      endPhase();
      break;
  }
}
