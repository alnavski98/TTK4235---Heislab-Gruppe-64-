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
} elevatorState;



elevatorState elevatorInit(); //Initiate elevator with undefined state
void printElevatorState(elevatorState elevator);
//state getElevatorState();void openDoor();
void closeDoor();
//int getElevatorFloor();
//void setElevatorState(state State);
//void setElevatorFloor(int Floor);
//void setElevatorDirection(MotorDirection dir);
//void setNewCurrentOrder();
void move(MotorDirection dir);
void stopElevator();
int compareFloor(int Floor, int floorRequest); // This function has access to both state of elevator and pulling of floor sensor.
int requestIsAbove(int Floor, int floorRequest);
void openDoor();
void closeDoor();
//void getRequest();
