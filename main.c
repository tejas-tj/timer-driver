/**
 * @file main.c
 * @brief This program is written to toggle an LED at every 509 milliseconds.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "boards.h"
#include "hal_gpio.h"
#include "timer_driver.h"

/**
 *@brief This funtion is responsible for toggling of LED. 
 */
void led_blink(void){
	/*LED 2 toggle*/
	hal_gpio_pin_toggle(LED_2);
}

/**
 * @brief This fuction is the main entry for the application
 */
int main(void){
	/*Configuring LED 2 as output with default value 1*/
	hal_gpio_cfg_output(LED_2, 1);
	/*starting timer for 509 milliseconds*/
	timer_start(509000, led_blink);
	/*to run program indefinately long with core remain idle excpet when it toggles LED*/
	while(1){}
	return 0;
}

/**
 * @}
 */
