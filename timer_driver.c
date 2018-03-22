/**
 * @file timer_driver.c
 * @brief : This file contains defination for funtions written in timer driver header file.
 * This is for simple timer driver which will generate a event after specific duration (in us)
 */
#include "timer_driver.h"

/*General defination for Enable and Disable for positive logic*/
#define GENERIC_Enable 1
#define GENERIC_Disable 0

/*dummy function pointer to make scope of callback pointer global*/
void (*irq_handler)(void)		= NULL;

void timer_start(uint32_t Duration, void(*cb_handler)(void))
{
	irq_handler 			= cb_handler;
	NVIC_DisableIRQ(TIMER2_IRQn);
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	/*Clear the privious value stored in Timer2*/
	NRF_TIMER2->TASKS_CLEAR		= GENERIC_Enabled;
	/*Prescaler is set to get 1 us duration between 2 time pulses*/
	/*[Prescaler = (int)log_base2_(16MHz/invr(req_time_interval))]*/
	NRF_TIMER2->PRESCALER		= 4;
	/*Timer mode is selected for TImer2*/
	NRF_TIMER2->MODE		= TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
	/*32 bit-mode is selected*/
	NRF_TIMER2->BITMODE		= TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;
	/*Disable the timer interrupt if it's already enabled*/
	NRF_TIMER2->INTENCLR		= TIMER_INTENCLR_COMPARE0_Enabled << TIMER_INTENCLR_COMPARE0_Pos;
	/*Set match value to value from main application*/
	NRF_TIMER2->CC[0]		= Duration;
	/*Timer peripheral interrupt enabled*/
	NRF_TIMER2->INTENSET		= TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
	/*Timer core interrupt enabled*/
	NVIC_EnableIRQ(TIMER2_IRQn);
	/*Priority is set to 1*/
	NVIC_SetPriority(TIMER2_IRQn, 1);
	/*Timer start*/
	NRF_TIMER2->TASKS_START		= GENERIC_Enabled;
	/*Clear the counter on CC[0] match*/	
	NRF_TIMER2->SHORTS		= TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
}

/**
 * @brief : This is ISR routine which will be called at timmer interrupt.
 */

void TIMER2_IRQHandler(){
	if(NRF_TIMER2->EVENTS_COMPARE[0]){
		/*Reset compare event*/
		NRF_TIMER2->EVENTS_COMPARE[0] = GENERIC_Disabled;
	}
	/*Call to callback function*/
	irq_handler();
}

void timer_stop(){
	/*Stop timer from counting further*/
	NRF_TIMER1->TASKS_STOP		= GENERIC_Enabled;
	/*Clear timer value to avoid the generation of garbage value*/
	NRF_TIMER1->TASKS_CLEAR		= GENERIC_Enabled;
	/*Timer shutdown to save power*/
	NRF_TIMER1->TASKS_SHUTDOWN	= GENERIC_Enabled;
}
/**
 * @}
 * @}
 */
