/****************************************************
 * TaskSetup.h
 * 
 * Setup the CapTin tasks
 * 
 ****************************************************/
#ifndef _TASKSETUP_H_
#define _TASKSETUP_H_

/**********************
 * Includes
 **********************/
#include <FreeRTOS.h>
#include <task.h>
#include "cmn/Errors.h"

/**********************
 * Defines
 **********************/
#define TASK_MIN_STACK 4096

/**********************
 * Types
 **********************/
enum
{
    tskMED_PRIORITY,
    tskHIGH_PRIORITY,
};

/**********************
 * Function Prototypes
 **********************/

/**********************
 * Variables
 **********************/

/**********************
 * Functions
 **********************/
ct_err_t Init_Task_CapTin( );
ct_err_t Init_Task_TicTacToe( );
ct_err_t Init_Task_SlotMachine( );

#endif