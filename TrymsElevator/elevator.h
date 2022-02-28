#pragma once

#include <stdio.h>
#include "elevio.h"

typedef enum {
    UNDEFINED = 0,
    IDLE,
    MOVING,
    DOOROPEN,
    OBSTRUCTION,
    STOPBUTTON,
} state; //Need to have state after the enum to use it in the script. 

typedef struct {
    state State;
    int Floor;
    MotorDirection Dir;
    int currentFloorRequest;
    int requestInDIr;
} elevatorState;

elevatorState elev; // Global elevator instance that we use. 



//elevatorState elevatorInit(); //Initiate elevator with undefined state
void initElevator(); //Initiate elevator with undefined state

//void printElevatorState(elevatorState* elevator);
void printElevatorState();

void closeDoor();
void move(MotorDirection dir);
void stopElevator();
int checkIfOnFloor(int floor); // This function has access to both state of elevator and pulling of floor sensor.
int requestIsAbove();
void openDoor();
void closeDoor();
void pollFloorSensor();
void pollStopButton();
void pollObstructionButton();
