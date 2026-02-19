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
#include "cmn/ControlTouch.h"

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

typedef uint32_t ntfy_app_t8;
enum
{
    NTFY_NONE,
    NTFY_SETUP,
    NTFY_PRDC,
    NTFY_SUSPEND,
};

/* All User and Kernel Apps */
typedef uint8_t app_list_t8;
enum
{
    /* User Apps*/
    APP_TICTACTOE,
    APP_SLOTMACHINE,
    APP_HACKER,
    APP_TOUCHTIME,
    APP_USER_LAST = APP_TOUCHTIME,

    /* Kernel Apps */
    APP_CAPTIN,
    APP_DEV,
    APP_KRNL_LAST = APP_DEV,

    APP_COUNT_USER = APP_USER_LAST + 1,
    APP_COUNT_TOTAL = APP_KRNL_LAST + 1,
};

/* Type alias */
using TaskSetupFunction = void (*)(void);

typedef struct 
{
    TaskHandle_t tsk_hndl;
    TaskSetupFunction setup_fnctn;

} CapTin_Hook_s;

/**********************
 * Function Prototypes
 **********************/
void GetCapTinHooks( CapTin_Hook_s hooks[ APP_COUNT_TOTAL ] );
void CapTinResume( );

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
ct_err_t Init_Task_TouchTime( );

#endif