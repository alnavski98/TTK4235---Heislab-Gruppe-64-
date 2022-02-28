/**
* @file
* @brief A library containing state machine functionality
*/

# pragma once
#include "elevio.h"
#include <stdio.h>

/**
* @struct Request requestManager.h
* @brief struct for storing number of requests currently treated by the elevator system
* and from which floor the request(s) is/are coming from
*/
typedef struct {
    /** Number of requests*/
    int numRequest;
    /** Which floor the request is coming from*/
    int Database[N_BUTTONS][N_FLOORS];
} Request;

/**
* @brief Initializes database containing requests by setting number of requests
* and at which floor the request(s) is/are coming from to 0
*
* @return Instance of Request called "requestDatabase" where all values are 0
*/
Request initRequestDatabase();

/**
* @brief Updates the request database and lights the lamp where the button is pressed
*
* @param[in,out] requestDatabase Request struct where its Database is to be updated
* to 1 wherever the button and floor matches 
*/
void updateRequests(Request* requestDatabase);

/**
* @brief Updates the number of requests currently stored in the database
*
* @param[in,out] database Request struct where its numRequest is to be updated
*/ 
void updateNrRequests(Request* database);


//int isRequest();

/**
* @brief Gets floor represented by an integer which the elevator should move to based
* on a request from the client
*
* @details If the elevator has stopped, it loops through all available buttons, and
* if there exist a stored request (1) in the database at the current floor it returns that floor.
*
* @details If the previously visited floor is below the 3rd floor, it loops through all floors
* in the reverse direction (from the 4th to the 1st) and all buttons. The first floor it
* encounters where there is a stored request (1) in the database, it returns the corresponding floor
*
* @details If the previously visited floor is on the 3rd floor or above, it loops through all floors
* (from the 1st to the 4th) and all buttons. The first floor it encounters where there is a stored
* request (1) in the database, it returns the corresponding floor
*
* @param[in] elevatorFloor Current floor elevator is on/last visited 
*
* @param[in] dir Current direction of the elevator
*
* @param[in] database 2D-array to be read to check which floor the request is coming from
*
* @return Floor the request is coming from 
*/ 
int getRequest(int elevatorFloor,int dir, int database[N_BUTTONS][N_FLOORS]);

/**
* @brief Specifies if the next floor (either above or below the current) exists in the
* database 
*
* @details If the elevator moves in the upwards direction and there's a non-zero difference
* between the requested and current floor, it returns the floor right above the previously
* visited one if it exists in the database
*
* @details If the elevator moves in the downwards direction, it does the same as with the 
* upwards direction with the difference being that it returns the floor right below 
* if it exists in the database
*
* @param[in,out] elevatorFloor Current floor
*
* @param[in] dir Motor direction
*
* @param[in] currentRequest Current floor requested by client
*
* @param[in] database Database containing requested floor 
*
* @return The next floor (either above or below the current) if there exist a request in
* the database at that floor, otherwise -1
*/
int getRequestInDIrection(int elevatorFloor, MotorDirection dir, int currentRequest, int database[N_BUTTONS][N_FLOORS]);
//void addRequest();

/**
* @brief Deletes an individual request in the @p database on the floor specified by @p floor 
*
* @details Request gets deleted by setting the @p batabase equal to 0 on floor(s) @p floor 
* location(s) in its array/table, and decrements the number of total requests by 1  
*
* @param[in] floor Floor where the request is to be deleted in the database
*
* @param[in,out] database Container for which floor and button a/several request(s) exist
*/
void deleteRequest(int floor, Request* database);

/**
* @brief Deletes all requests in the @p database
*
* @details Sets the number of requests and all the values in @p database equal to 0,
* and turns off all button lights
*
* @param[in,out] database Container for which floor and button a/several request(s) exist
*/
void deleteAllRequests(Request* database);