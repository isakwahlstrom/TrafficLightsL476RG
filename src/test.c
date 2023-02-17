/**
******************************************************************************
@brief   test, tests for Project-program
@file    test.c
@author  Isak Wahlström
@version 1.0
@date    30-11/2022
@brief   tests for LED:s and buttons and switches
******************************************************************************
*/
#include "test.h"
#include "main.h"
#include "project_functions.h"
#include "stdbool.h"


/**
@brief testprogram to run each of the functions.

@param void

@return void
*/
void Test_program(void)
{
	//setbits(0);
	//Test_buttons();
	//test_start();
	//Test_led();

}
/**
@brief function to testAllLeds

@param uint32_t bits , bitpattern to which lights to turn on or off

@return void
*/

void Test_led(void) {
	setbits(16184);
}
/**
@brief function to test the buttons and switches!

@param void

@return void
*/

void Test_buttons(void) {
	while(1) {
		if(TL1_hit()) {
			Test_led();
		}
		if(TL2_hit()) {
			Test_led();
		}
		if(TL3_hit()) {
			Test_led();
		}
		if(TL4_hit()) {
			Test_led();
		}
		if(PL1_hit()) {
			Test_led();
		}
		if(PL2_hit()) {
			Test_led();
		}
	}
}
/**
@brief function to test if blue light turns on.

@param

@return void
*/

void test_start(void)  {
	PedestrianRedCarGreen();
	while(1) {
		if(PL2_hit()) {
			pedestrianRedCarGreenBlue();
		}
	}
}
/**
@brief function to test if pedestriangreenlights turns on

@param void

@return void
*/
void test_pedestriangreen(void) {
	//setbits(0b0000000000000000000101000010000); orange
	setbits(0b0000000000000000001000100001000);
}

/**
@brief function to test orangelights.

@param void

@return void
*/

void test_orange(void) {
	setbits(0b0000000000000000000101000010000);
}

/**
@brief function to test if Tick works.

@param void

@return void
*/

void Test_tick(void) {
	uint8_t startTime = 0;
	uint8_t deltaTime = 0;
	startTime = HAL_GetTick();
	HAL_Delay(200);
	deltaTime = HAL_GetTick() - startTime;

}
/**
@brief function to test if toggling between blue lights on/off works.

@param void

@return void
*/

void test_Toggle(void) {
	uint32_t frequency = 0;
	while(1) {
		frequency = HAL_GetTick();
		if(frequency%10==0) {
			pedestrianRedCarGreenBlue();
		} else {
			PedestrianRedCarGreen();
		}
	}

}
