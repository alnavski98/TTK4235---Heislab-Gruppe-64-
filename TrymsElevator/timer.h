/**
* @file
* @brief A library for keeping track of time
*/

# pragma once

#include <time.h>

/**
* @brief Returns starting processor time and is used to start
* the timing of a process
*
* @return processor clock time (at start) 
*/
clock_t startTimer();
/**
* @brief Returns ending processor time and is used to end
* the timing of a process
*
* @return processor clock time (at end)
*/
clock_t endTimer();
/**
* @brief Calculates the time spent from when 
*
* @param[in] end Processor clock time indicating the end of the
* functionality one wants to time
*
* @param[in] start Processor clock time indicating the start of the 
* functionality one wants to time
*
* @return spent time between @p start and @p end as a decimal value
* by using the conversion factor CLOCKS_PER_SEC 
*/
double timeSpent();