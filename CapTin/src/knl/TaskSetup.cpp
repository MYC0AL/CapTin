/****************************************************
 * TaskSetup.cpp
 * 
 * Setup the CapTin tasks
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "knl/TaskSetup.h"
#include "app/AppCapTin.h"
#include "app/AppDev.h"
#include "app/AppTicTacToe.h"
#include "app/AppSlotMachine.h"
#include "app/AppHacker.h"
#include "cmn/Config.h"

/**********************
 * Defines
 **********************/

/**********************
 * Function Prototypes
 **********************/

/**********************
 * Variables
 **********************/
static CapTin_Handles_t _handles;

#if ( CFG_DEV )
static TaskHandle_t _dev_handle;
#endif

/**********************
 * Functions
 **********************/
/***************************************************
 * GetCapTinHandles()
 * 
 * Description: Return a struct of all task handles
 **************************************************/
void GetCapTinHandles( CapTin_Handles_t handles )
{
    memcpy( handles, _handles, sizeof( TaskHandle_t ) * APP_COUNT );
}

/***************************************************
 * Init_Task_CapTin()
 * 
 * Description: Create the CapTin task and app
 **************************************************/
ct_err_t Init_Task_CapTin( )
{
    xTaskCreate
        (
        CapTin_run,
        "CapTin",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &_handles[ APP_CAPTIN ]
        );

    return ERR_NONE;
}

/***************************************************
 * Init_Task_Dev()
 * 
 * Description: Creat the Dev task
 **************************************************/
ct_err_t Init_Task_Dev( )
{
    xTaskCreate
        (
        Dev_run,
        "Dev",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &_dev_handle
        );

    return ERR_NONE;
}

/***************************************************
 * Init_Task_TicTacToe()
 * 
 * Description: Create the TicTacToe task
 **************************************************/
ct_err_t Init_Task_TicTacToe( )
{
    xTaskCreate
        (
        TicTacToe_run,
        "TicTacToe",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &_handles[ APP_TICTACTOE ]
        );

    return ERR_NONE;
}

/***************************************************
 * Init_Task_SlotMachine()
 * 
 * Description: Create the Slot Machine task
 **************************************************/
ct_err_t Init_Task_SlotMachine( )
{
    xTaskCreate
        (
        SlotMachine_run,
        "SlotMachine",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &_handles[ APP_SLOTMACHINE ]
        );

    return ERR_NONE;  
}

/***************************************************
 * Init_Task_Hacker()
 * 
 * Description: Create the Hacker task
 **************************************************/
ct_err_t Init_Task_Hacker( )
{
    xTaskCreate
        (
        Hacker_run,
        "Hacker",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &_handles[ APP_HACKER ]
        );

    return ERR_NONE;
}
