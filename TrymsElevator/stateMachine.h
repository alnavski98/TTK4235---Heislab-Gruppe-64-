/**
* @file
* @brief A library containing state machine functionality
*/

#pragma once
#include "elevator.h"
#include "timer.h"
# include "requestManager.h"

/**
* @brief Uses elevator, timer and requestManager functionality
* to keep track of the different states for the elevator
*/
void stateMachine();