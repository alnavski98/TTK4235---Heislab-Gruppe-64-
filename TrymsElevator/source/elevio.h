/**
* @file
* @brief A driver module containing low level elevator functionality. 
*/

#pragma once


#define N_FLOORS 4

/**
* @enum MotorDirection elevio.h
* @brief Defines three physical states of the elevator Motor. It can move up, down or stand still. 
*/
typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

/**
* @enum ButtonType elevio.h
* @brief Defines physical buttons outside and inside the elevator. 
*/
typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;


/**
* @brief Initialize the physical connection to the elevator server.
*/ 
void elevio_init(void);


/**
* @brief Set the motor direction of the elevator. 
* @param[in] dirn Parameter defining the requested motor direction. 
*/ 
void elevio_motorDirection(MotorDirection dirn);

/**
* @brief Set the lamp on the elevator buttons. 
* @param[in] floor Floor the button is on.
* @param[in] button Button to light up.
* @param[in] value 1 if turn on, 0 if turn of. 
*/ 
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
* @brief Set the floor lamp.
* @param[in] floor Floor lamp to turn on. 
*/ 
void elevio_floorIndicator(int floor);

/**
* @brief Set the door open lamp. 
* @param[in] value 1 if turn on, 0 if turn of.
*/ 
void elevio_doorOpenLamp(int value);

/**
* @brief Set the stop button lamp. 
* @param[in] value 1 if turn on, 0 if turn of.
*/ 
void elevio_stopLamp(int value);

/**
* @brief Checking if any specific buttons are pressed. 
* @param[in] floor Floor number of the button.
* @param[in] button Button to check. 
*/ 
int elevio_callButton(int floor, ButtonType button);

/**
* @brief Returns data from the floor sensor. 
*/ 
int elevio_floorSensor(void);

/**
* @brief Returns data from the stop button.
*/ 
int elevio_stopButton(void);

/**
* @brief Returns data from the obstruction switch.
*/ 
int elevio_obstruction(void);

