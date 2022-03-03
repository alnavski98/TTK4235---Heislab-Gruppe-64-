#pragma once

#include <stdio.h>
#include "elevio.h"

typedef enum {
    UNDEFINED = 0,
    IDLE,
    IDLEINBETWEEN,
    MOVING,
    DOOROPEN,
    OBSTRUCTION,
    STOPBUTTON,
} state; 

typedef struct {
    state State;
    int Floor;
    MotorDirection Dir[2];
    int currentFloorRequest;
    int requestInDIr;
} elevatorState;

elevatorState elev; // Global elevator instance that we use. 


void initElevator(); 
void printElevatorState();
void moveElevator(MotorDirection dir);
void stopElevator();
void openDoor();
void closeDoor();


void pollFloorSensor();
void pollStopButton();
void pollObstructionButton();