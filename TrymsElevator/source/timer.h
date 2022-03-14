/**
* @file
* @brief A timer module providing useful functionality for the elevator door and stop button. 
*/

# pragma once
#include <time.h>


clock_t start;
clock_t end;


/**
* @brief Returns an instance of a processor time. 
*
* @return Number of clock ticks elapsed since start of program. 
*/
clock_t startTimer();



/**
* @brief Returns an instance of a processor time. 
*
* @return Number of clock ticks elapsed since start of program. 
*/
clock_t endTimer();




/**
* @brief Calculates the time spent between a start time and an end time.
*
* @return spent time between @p start and @p end in seconds given as double.  
*/
double timeSpent();
