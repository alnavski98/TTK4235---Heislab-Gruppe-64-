/**
* @file
* @brief A library containing high level elevator functionality 
*/

#pragma once

#include <stdio.h>
#include "elevio.h"

/**
* @enum state elevator.h
* @brief Possible states the elevator can be in at any given time
*/
typedef enum {
    /** Elevator is not on or inbetween floors,
    and is only present during startup*/
    UNDEFINED = 0,
    /** Elevator is on floor*/ 
    IDLE, 
    /** Elevator is inbetween two (defined) floors*/ 
    INBETWEEN,
    /** Elevator is moving*/ 
    MOVING, 
    /** Elevator door is open (while on floor)*/
    DOOROPEN, 
    /** Obstruction switch is activated*/
    OBSTRUCTION,
    /** Stop button has been pressed*/ 
    STOPBUTTON, 
} state; //Need to have state after the enum to use it in the script. 

/**
* @struct elevatorState elevator.h
* @brief Data values holding state and return values from functions in order for the elevator to function properly
*/
typedef struct {
    /** Variable keeping track of the elevator's current state such as IDLE, MOVING etc.*/
    state State;
    /** Variable storing the elevator's current floor*/
    int Floor;
    /** Variable storing the previous floor the elevator visited*/
    int PrevFloor;
    /** Variable keeping track of the current direction of the elevator (upwards, downwards or still)*/
    MotorDirection Dir;
    /** Variable storing the current floor request*/
    int currentFloorRequest; // Represents the floor at which the request comes from
} elevatorState;


/** 
* @brief Initializes the elevators properties
*
* @return Instance of elevatorState called "elevator" containing values corresponding to system startup 
*
*/
elevatorState elevatorInit(); //Initiate elevator with undefined state

/**
* @brief Displays current elevatorState values for the elevator at any time the function is called upon
*/
void printElevatorState(elevatorState elevator);

//state getElevatorState();void openDoor();
/**
* @brief Closes elevator door
*/
void closeDoor();

//int getElevatorFloor();
//void setElevatorState(state State);
//void setElevatorFloor(int Floor);
//void setElevatorDirection(MotorDirection dir);
//void setNewCurrentOrder();

/**
* @brief Moves elevator in direction specified by @p dir
*
* @param[in] dir Enumaration value representing the direction which the elevator should move,
* where -1 = downwards, 0 = stop, 1 = upwards
*/
void move(MotorDirection dir);

/**
* @brief Stops elevator
*/
void stopElevator();

/**
* @brief Checks if elevator's current floor matches the floor requested by the client
*
* @param[in] Floor Current floor elevator has visited/is on
*
* @param[in] floorRequest Floor requested by the client
*
* @return 1 if the floor's match, otherwise 0
*/
int compareFloor(int Floor, int floorRequest); // This function has access to both state of elevator and pulling of floor sensor.

/**
* @brief Checks if the floor requested by the client is at a higher floor than the elevator's current floor
*
* @param[in] Floor Current floor elevator has visited/is on
*
* @param[in] floorRequest Floor requested by the client
*
* @return 1 if the floor requested is greater than the current floor, otherwise 0
*/
int requestIsAbove(int Floor, int floorRequest);

/**
* @brief Opens the elevator door
*/
void openDoor();

/**
* @brief Closes the elevator door
*/
void closeDoor();
//void getRequest();
