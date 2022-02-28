/**
* @file
* @brief A library containing low level elevator functionality
*/

#pragma once

#define N_FLOORS 4

/**
* @enum MotorDirection elevio.h
* @brief Possible directions the motor of the elevator is currently moving at any time
*/
typedef enum { 
    /** Moving downwards*/
    DIRN_DOWN   = -1,
    /** Stopping*/
    DIRN_STOP   = 0,
    /** Moving upwards*/
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

/**
* @enum ButtonType elevio.h
* @brief Values representing what type of button is requesting the elevator
*/
typedef enum { 
    /** Up button (outside cab)*/
    BUTTON_HALL_UP      = 0,
    /** Down button (outside cab)*/
    BUTTON_HALL_DOWN    = 1,
    /** Cab button*/
    BUTTON_CAB          = 2
} ButtonType;

/**
* @brief Initializes the elevator connecting to the one in the lab or the server
*/ 
void elevio_init(void);

void elevio_motorDirection(MotorDirection dirn);
void elevio_buttonLamp(int floor, ButtonType button, int value);
void elevio_floorIndicator(int floor);
void elevio_doorOpenLamp(int value);
void elevio_stopLamp(int value);

int elevio_callButton(int floor, ButtonType button);
int elevio_floorSensor(void);
int elevio_stopButton(void);
int elevio_obstruction(void);

