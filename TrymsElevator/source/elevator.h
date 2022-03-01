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
} state; //Need to have state after the enum to use it in the script. 

typedef struct {
    state State;
    int Floor;
    MotorDirection Dir[2];
    int currentFloorRequest;
    int requestInDIr;
} elevatorState;

elevatorState elev; // Global elevator instance that we use. 


//elevatorState elevatorInit(); //Initiate elevator with undefined state
void initElevator(); //Initiate elevator with undefined state
void printElevatorState();
void closeDoor();
void moveElevator(MotorDirection dir);
int getFloorSensor();
int getStopButton();
int getObstruction();
void stopElevator();
void openDoor();
void closeDoor();
void turnOnFloorLamp(int Floor);


