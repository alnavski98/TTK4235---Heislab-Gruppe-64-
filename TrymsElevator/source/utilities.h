/**
* @file
* @brief A utilities module defining useful functions for cleaner and more readable code. 
*/

#pragma once

#include "elevator.h"
#include "timer.h"


/**
* @brief Executing specific steps when a floor is reached. 
* @details It stops the elevator, opens the door, delete the requests on that floor and starts a timer. 
*/
void floorReached();

/**
* @brief Checks if the input floor is equal to the elevator floor. 
*
* @param[in] Floor Integer between 0 and 3. 
*
* @return 1 if the floor's match, otherwise 0
*/
int checkIfOnFloor(int floor); 

/**
* @brief Checks if the elevators current request is above or below the elevator floor. 
*
* @return 1 if the requested floor is greater than the elevator floor, otherwise 0
*/
int requestIsAbove();

