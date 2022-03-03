#pragma once

#include "elevio.h"
#include "elevator.h"
#include "requestManager.h"
#include "timer.h"

void floorReached();
void waitStopUnpressed();

int checkIfOnFloor(int floor); 
int requestIsAbove();

int getFloorSensor();
int getStopButton();
int getObstruction();
void turnOnFloorLamp(int Floor);