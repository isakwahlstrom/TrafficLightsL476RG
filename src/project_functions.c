
/**
******************************************************************************
@brief   Project, functions for Project-program
@file    project_functions.c
@author  Isak Wahlström
@version 1.0
@date    30-11/2022
@brief   Functions and structures for program project.
******************************************************************************
*/
#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "stdbool.h"

const uint32_t pedred = 3104;
const uint32_t pedredblue = 11296;
const uint32_t pedestriaGreen = 4360;
const uint32_t orangeblue = 10768;
const uint32_t orangelight = 2576;
/**
@brief function to turn the corresponding bits to 1 or 0.

@param uint32_t bits , bitpattern to which lights to turn on or off

@return void
*/

void setlights(uint32_t bits){
      bits = bits<<8;

      HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET); // Sätter låg

      HAL_SPI_Transmit(&hspi3, &bits, 4, 10); // Skickar bit

      HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET); // Sätta STCP HÖG


      HAL_GPIO_WritePin(Enable_595_GPIO_Port, Enable_595_Pin, GPIO_PIN_RESET); // Enable låg.


      HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
  }

/**
@brief function to read PL2buttons

@param void

@return void
*/

bool PL2_hit(void) {
	  if(HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET) {
		  return true;
	  } else {
		  return false;
	  }
 }


/**
@brief function to toggle between red car lights and blue lights on and off

@param uint32_t the frequency to toggle the blue lights with

@return void
*/
void toggleWaiting(uint32_t frequency) {
	if(frequency%400==0) {
		setlights(pedredblue);
	} else {
		setlights(pedred);
	}
}

/**
@brief function to toggle between orange and blue lights on and off

@param uint32_t the frequency to toggle the blue lights with

@return void
*/

void toggleOrange(uint32_t frequency) {
	if(frequency%400==0) {
		setlights(orangeblue);
	} else {
		setlights(orangelight);
	}
}

/**
@brief function to transition between pedestrian lights green to red.

@param uint32_t orangeTime the time the orange lights are turned on.

@return void
*/

void pedestrianGreentoRed(uint32_t orangeTime) {
	setlights(orangelight); // Put orange
	HAL_Delay(orangeTime); // for 1 seconds.
	setlights(pedred);// back to pedestrian red.
}
uint32_t getTime(void) {
	return HAL_getTick();
}


