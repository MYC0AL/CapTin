/****************************************************
 * ControlTouch.h
 * 
 * Control the TAMC_GT911 Touch Library
 * 
 ****************************************************/
#ifndef _CONTROLTOUCH_H_
#define _CONTROLTOUCH_H_

/**********************
 * Includes
 **********************/
#include <TAMC_GT911.h>
#include "cmn/Errors.h"

/**********************
 * Defines
 **********************/
#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 18

#define TOUCH_INT -1
#define TOUCH_RST 38

#define TOUCH_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 480
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 480
#define TOUCH_MAP_Y2 0
#define TOUCH_MAX 5

/**********************
 * Types
 **********************/

/**********************
 * Variables
 **********************/

/**********************
 * Functions
 **********************/
TAMC_GT911* Touch_getDriver( );
err_t Touch_getTouches( TP_Point touches[TOUCH_MAX], uint8_t* touch_count );

#endif