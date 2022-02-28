#pragma once
#include "timer.h"
#include "requestManager.h"
#include "elevator.h"

void stateUNDEFINED();
void stateIDLE();
void stateMOVING();
void stateDOOROPEN();
void stateOBSTRUCTION();
void stateSTOPBUTTON();
void stateMachine();