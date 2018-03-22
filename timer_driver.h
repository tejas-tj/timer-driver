/**
 * @file timer_driver.h
 * @ brief This header file contains declartions for timer driver funtions.
 * This is the sample timer driver to generate event at every specific duration (in ms)
 * Here call back funtions and timer interrupts are used.*
 */

#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include "boards.h"
#include "nrf.h"

/**
 * @brief This funtion is used to generate event at every specific duration in microseconds specified by application program
 * @param Duration : This parameter specifies the delay between two events in micro-seconds
 * @param cb_handler : This is the pointer pointing to the function which is to be called
 */
void timer_start(uint32_t Duration, void (*cb_handler)(void));

/**
 * @brief : This fuction is used to stop infinite occurance of timer driven events
 */
void timer_stop(void);

#endif /*TIMER-DRIVER_H*/
/**
 * @}
 * @}
 */
