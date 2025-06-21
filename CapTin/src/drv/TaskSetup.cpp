/****************************************************
 * TaskSetup.cpp
 * 
 * Setup the CapTin tasks
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "drv/TaskSetup.h"
#include "app/AppCapTin.h"

/**********************
 * Defines
 **********************/

/**********************
 * Function Prototypes
 **********************/

/**********************
 * Variables
 **********************/
TaskHandle_t th_CapTin;

/**********************
 * Functions
 **********************/

/***************************************************
 * Init_Task_CapTin()
 * 
 * Description: Create the CapTin task and app
 **************************************************/
err_t Init_Task_CapTin( )
{
    xTaskCreate
        (
        CapTin_run,
        "CapTin",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &th_CapTin
        );

    return ERR_NONE;
}
