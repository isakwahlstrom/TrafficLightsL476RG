/**
******************************************************************************
@brief   Project, task 1
@file    task1.c
@author  Isak Wahlström
@version 1.0
@date    30-11/2022
@brief   The program for pedestrian lights with state machine
******************************************************************************
*/

#include "project_functions.h"
#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "stdbool.h"

const uint32_t pedestrianRedCarGreen = 3104;
const uint32_t pedredcargreenblue = 11296;
const uint32_t pedgreen = 4360;


/**
 * @brief the pedestriancrossing, including toggling blue light as well as buttons and timestamps.
 * @param void
 * @return void
 */
void task1(void) {

	typedef enum
	{pedestrianRed,
	 pedestrianGreen,
	 pedestrianWaiting
	} states;
	static states pedestrianState;

	uint32_t toggleFreqms = 0;
	uint32_t walkingDelay =0;
	uint32_t orangeDelay = 1000;
	uint32_t pedestrianDelay=0;
	uint32_t pedestrianPressTime = 0;
	uint32_t greenStateTime = 0;
	setlights(pedestrianRedCarGreen);
	pedestrianState = pedestrianRed;
	while(1) {
		switch(pedestrianState) {
			case pedestrianRed:
				if(PL2_hit()) {
					setlights(pedredcargreenblue);
					pedestrianState = pedestrianWaiting; // Change state.
					pedestrianPressTime=HAL_GetTick();
					pedestrianDelay = HAL_GetTick();
				} else {
					pedestrianState = pedestrianRed; // Else stay in same state;
				}
					break;

			case pedestrianWaiting:
				toggleFreqms = HAL_GetTick()-pedestrianPressTime;
				pedestrianDelay = HAL_GetTick()-pedestrianPressTime;
				if(pedestrianDelay<=2000) {
					toggleWaiting(toggleFreqms);
				} else {

					if(pedestrianDelay<=3000) {
						toggleOrange(toggleFreqms);
					} else {
						pedestrianState = pedestrianGreen; // Change state.
						greenStateTime = HAL_GetTick();
						pedestrianDelay = 3000;
					}
				}
					break;

			case pedestrianGreen:
				walkingDelay = HAL_GetTick()-greenStateTime;
				if(pedestrianDelay==3000 && walkingDelay<2000) { // if green for pedestrians == 3 seconds
					setlights(pedgreen);
				} else {
					pedestrianState = pedestrianRed; // change state
					pedestrianGreentoRed(orangeDelay);
				}
					break;


		}
	}
}
