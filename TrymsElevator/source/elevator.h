/**
* @file
* @brief A module containing high level elevator functionality 
* @details Storing and modifying real time information on the elevator. It also uses the elevator driver to control it. 
*/

#pragma once

#include <stdio.h>
#include "elevio.h"

/**
* @enum state elevator.h
* @brief Defined states the elevator can have at any given time
*/
typedef enum {
    /** Startup state and only entered once.*/
    UNDEFINED = 0,
    /** Elevator is on a floor and waiting for a request.*/ 
    IDLE,
    /** Elevator is inbetween two (defined) floors and waiting for a request.*/ 
    IDLEINBETWEEN,
    /** Elevator is moving to requested floor-*/ 
    MOVING,
    /** Elevator door is open.*/
    DOOROPEN,
    /** Obstruction switch is activated.*/
    OBSTRUCTION,
    /** Stop button has been pressed.*/ 
    STOPBUTTON,
} state; 


/**
* @struct elevatorState elevator.h
* @brief A struct containing real time information on the elevator. 
*/
typedef struct {
    /** Variable keeping track of the elevator's current state.*/
    state State;
     /** Integer storing the elevator's current floor.*/
    int Floor;
    /** Array storing the MotorDirection of the elevator, and also the last MotorDirection when stopButton is pressed.*/
    MotorDirection Dir[2];
     /** Integer holding the current request.*/
    int currentFloorRequest;
    /** Integer storing information on requests on next floor in the direction of travel.*/
    int requestInDIr;
} elevatorState;

elevatorState elev; 

/** 
* @brief Initializes the elevator status. 
* @details Sets state to UNDEFINED, sets requests and floor to -1, and motorDirection to stop. 
*/
void initElevator(); 

/**
* @brief Displays the current elevatorState.
*/
void printElevator();

/**
* @brief Moves elevator in direction specified by @p dir
*
* @param[in] dir MotorDirection to set the elevator to.
*/
void moveElevator(MotorDirection dir);

/**
* @brief Stops the elevator.
*/
void stopElevator();


/**
* @brief Opens the elevator door, or in this case door lamp is turned on.
*/
void openDoor();

/**
* @brief Closes the elevator door, or in this case door lamp is turned off.
*/
void closeDoor();


/**
* @brief Polls the floor sensor. 
* @details Checks the floor sensor and updates the elevator floor and the floor lamp when there is a change.
*/
void pollFloorSensor();

/**
* @brief Polls stop button. 
* @details Checks the stop button sensor and updates the elevator state and the stop button lamp when there is a change.
*/
void pollStopButton();

/**
* @brief Polls obstruction switch. 
* @details Checks the obstruction switch and updates the elevator state when there is a change.
* @details Obstruction switch effect the system only when the elevator state is in DOOR OPEN when switched. 
*/
void pollObstructionButton();

/**
* @brief Gives current obstruction sensor data. 
*
* @return 1 if obstruction switch is active, 0 otherwise. 
*/
int getObstruction();

/**
* @brief Gives current stop button sensor data 
*
* @return 1 if stop button is active, 0 otherwise. 
*/
int getStopButton();

/**
* @brief Gives current floor sensor data. 
*
* @return -1 if inbetween floors, and a floor integer between 0 and 3 otherwise.
*/
int getFloorSensor();

/**
* @brief Sets the stop button lamp on or off depending on the value.
*
* @param[in] value 1 to turn on, 0 to turn off. 
*/
void setStopLamp(int value);

/**
* @brief Sets the button button lamp on or off depending on the value.
*
* @param[in] floor Floor the button is on.
* @param[in] button Button type.
* @param[in] value 1 to turn on, 0 to turn off. 
*/
void setButtonLamp(int floor, int button, int value);

/**
* @brief Checks if a specific button is pressed.
*
* @param[in] floor Floor the button is on.
* @param[in] button Button type.
* @return 1 if the button is pressed, 0 otherwise. 
*/
int checkButtonPress(int floor, int button);

/**
* @brief Turns on the floor lamp. 
*
* @details Only one floor lamp is on at any given time. Therefore, when a new floor lamp is turned on, the other floor lamp is turned off. 
*
* @param[in] floor Floor lamp to turn on.
*/
void turnOnFloorLamp(int Floor);


