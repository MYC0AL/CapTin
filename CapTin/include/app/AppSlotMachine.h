/****************************************************
 * SlotMachine.h
 * 
 * The Slot Machine Application
 * 
 ****************************************************/

#ifndef _APPSLOTMACHINE_H_
#define _APPSLOTMACHINE_H_

/**********************
 * Includes
 **********************/
#include "cmn/Errors.h"
#include <FreeRTOS.h>
#include "cmn/ControlDisplay.h"
#include "cmn/ControlTouch.h"
#include "arduino_sprite.h"
#include "sprites/m.h"
#include "sprites/a.h"
#include "sprites/man.h"
#include "sprites/reel.h"
#include <stdlib.h>
#include <iostream>

/**********************
 * Defines
 **********************/

/**********************
 * Types
 **********************/

/**********************
 * Variables
**********************/

/**********************
 * Functions
 **********************/
void SlotMachine_run( void * pvParameters );

/**********************
 * Classes
 **********************/

#endif