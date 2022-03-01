#pragma once

#include "elevio.h"
#include "elevator.h"
#include "requestManager.h"
#include "timer.h"

void floorReached();
void wait();


int checkIfOnFloor(int floor); // This function has access to both state of elevator and pulling of floor sensor.
int requestIsAbove();
void pollFloorSensor();
void pollStopButton();
void pollObstructionButton();

