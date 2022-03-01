#pragma once
#include "timer.h"
#include "requestManager.h"
#include "elevator.h"
#include "elevio.h"
#include "utilities.h"

void stateUNDEFINED();
void stateIDLE();
void stateIDLEINBETWEEN();
void stateMOVING();
void stateDOOROPEN();
void stateOBSTRUCTION();
void stateSTOPBUTTON();
void stateMachine();