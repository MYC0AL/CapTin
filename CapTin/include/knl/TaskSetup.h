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

/* App Count */
enum
{
    APP_CAPTIN,
    APP_TICTACTOE,
    APP_SLOTMACHINE,
    APP_HACKER,
    APP_COUNT,

    /* The Dev app is not accessable */
    APP_DEV,
};

typedef TaskHandle_t CapTin_Handles_t[ APP_COUNT ];

/**********************
 * Function Prototypes
 **********************/
void GetCapTinHandles( CapTin_Handles_t handles );

/**********************
 * Variables
 **********************/

/**********************
 * Functions
 **********************/
ct_err_t Init_Task_CapTin( );
ct_err_t Init_Task_Dev( );
ct_err_t Init_Task_TicTacToe( );
ct_err_t Init_Task_SlotMachine( );
ct_err_t Init_Task_Hacker( );

#endif