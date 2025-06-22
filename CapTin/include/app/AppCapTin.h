/****************************************************
 * AppCapTin.h
 * 
 * The CapTin Application
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "cmn/Errors.h"
#include <FreeRTOS.h>
#include "cmn/ControlDisplay.h"
#include "cmn/ControlTouch.h"

/**********************
 * Defines
 **********************/

/**********************
 * Function Prototypes
 **********************/

/**********************
 * Variables
 **********************/

/**********************
 * Functions
 **********************/

/***************************************************
 * Init_Task_CapTin()
 * 
 * Description: Mount the SD Card to access the
 * files.
 **************************************************/
void CapTin_run( void * pvParameters );
