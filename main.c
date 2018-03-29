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
//	if(BUTTON_1)	hal_gpio_pin_toggle(LED_1);
	hal_gpio_pin_toggle(LED_3);
//	if(BUTTON_2)	hal_gpio_pin_toggle(LED_4);
}

/**
 * @brief This fuction is the main entry for the application
 */
int main(void){
	/*Configuring LED 2 as output with default value 1*/
	hal_gpio_cfg_output(LED_2, 1);
	hal_gpio_cfg_output(LED_1, 0);
	hal_gpio_cfg_output(LED_3, 1);
	hal_gpio_cfg_output(LED_4, 0);
	hal_gpio_cfg_input(BUTTON_1, HAL_GPIO_PULL_DISABLED);
	hal_gpio_cfg_input(BUTTON_2, HAL_GPIO_PULL_DISABLED);
	/*starting timer for 509 milliseconds*/
	if(BUTTON_1)	hal_gpio_pin_toggle(LED_1);
	if(BUTTON_2)	hal_gpio_pin_toggle(LED_4);
	timer_start(1000000000, led_blink);
	/*to run program indefinately long with core remain idle excpet when it toggles LED*/
	while(1){if(BUTTON_1)	hal_gpio_pin_toggle(LED_1);if(BUTTON_2)	hal_gpio_pin_toggle(LED_4);}
	return 0;
}

/**
 * @}
 */
