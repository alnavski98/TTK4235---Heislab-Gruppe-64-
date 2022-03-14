/**
* @file
* @brief A module containing the finite state machine. 
*/

#pragma once
#include "utilities.h"
#include "elevator.h"
#include "requestManager.h"

/**
* @brief Functionality to execute when in the state UNDEFINED.
* @details Executed only ones at start up of elevator. 
* @details If the elevator is in between floors it will move down until it finds a defined floor.  
* @details 
*/
void stateUNDEFINED();

/**
* @brief Functionality to execute when in the state IDLE.
* @details The function checks for new current requests. 
* @details When there is a new request it first checks if it is on the elevator floor. If not, it moves the elevator in the correct direction. 
*/
void stateIDLE();

/**
* @brief Functionality to execute when in the state IDLE INBETWEEN.
* @details This function is similar to stateIDLE. 
* @details Only difference is when a request is received on the last elevator floor it moves it correctly to that floor, instead of opening door in between floors. 
*/
void stateIDLEINBETWEEN();

/**
* @brief Functionality to execute when in the state MOVING.
* @details Checks if the requested floor or request in direction is reached. 
*/
void stateMOVING();

/**
* @brief Functionality to execute when in the state DOOR OPEN.
* @details Keeps the door open for 3 seconds if the obstruction switch is not turned on. 
*/
void stateDOOROPEN();

/**
* @brief Functionality to execute when in the state OBSTRUCTION.
* @details Holds the door open until the switch is turned off. 
*/
void stateOBSTRUCTION();

/**
* @brief Functionality to execute when in the state STOP BUTTON.
* @details Stays in the stop button state until the button is unpressed. Nothing else is executing when in this state. 
* @details All requests are deleted. Door is opened if on a floor. 
*/
void stateSTOPBUTTON();


/**
* @brief The state machine executing the main functionality of the program. 
* @details It Initiates connection to server, and also initate the elevator and request manager. 
* @details Runs correct functionality based on the state of the elevator using a switch.  
*/
void stateMachine();