/**
* @file
* @brief A module defining the request manager. 
* @details Storing the button presses, processing of the request and modifies the database.   
*/


# pragma once
#include <stdio.h>
#include "elevator.h"


/**
* @struct Request requestManager.h
* @brief A struct storing information on the requestManager. 
*/
typedef struct {
    /** Number of requests currently active. */ 
    int numRequest;
    /** 2D database containing information on floor and button type.  */ 
    int Database[N_BUTTONS][N_FLOORS];
} Request;

Request requestManager;


/**
* @brief Initializes the requestManager. 
* @details Sets the matrix elements and number of requests to zero.
*/
void initRequestManager();


/**
* @brief Displays the database and number of requests. 
*/
void printRequestManager();



/**
* @brief Updates the request database when a button is pressed and lights the corresponding lamp.
*/
void pollElevatorButtons();



/**
* @brief Provides the next request to the elevator based on logic. The request is represented by the floor given as an int.
*
* @details It first checks for requests on the elevators current floor. 
*
* @details When there is no request on its current floor it loops through the rest of the database. 
* If the elevator is on floor 1 or 2, it loops through the database from floor 4 and downwards. 
* If the elevator is on floor 3 or 4, it loops through the database from floor 1 and upwards. 
*
* @details The new request is added directly to the elevators current request. 
*/ 
void getNewRequest();



/**
* @brief Checks if the next floor has a request, if it is not the requested floor, and informs the elevator only if the request is in the direction of travel. 
*
* @details If the elevator moves in the upwards direction, there is a floor between the elevator floor and the requested floor, and
* there is a cab or hall up request on that floor, it gives the information to the elevator. 
*/
void checkRequestInDirection();


/**
* @brief Deletes all request on the elevators floor from the database, and turns of the corresponding button lamps. 
*
* @details Request is deleted by setting the elements equal to zero in the request database. 
*/
void deleteRequestsOnFloor();


/**
* @brief Deletes all requests in the request database.
*
* @details Sets the number of requests and all the elements in the database equal to 0,
* and turns off all button lights.
*/
void deleteAllRequests();
