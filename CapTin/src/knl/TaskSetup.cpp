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
#include "app/AppTouchTime.h"
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
static CapTin_Hook_s _hooks[ APP_COUNT_TOTAL ];

/**********************
 * Functions
 **********************/
/***************************************************
 * GetCapTinHooks()
 * 
 * Description: Return a struct of all task handles
 **************************************************/
void GetCapTinHooks( CapTin_Hook_s hooks[ APP_COUNT_TOTAL ] )
{
    memcpy( hooks, _hooks, sizeof( CapTin_Hook_s ) * APP_COUNT_TOTAL );
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
        &_hooks[ APP_CAPTIN ].tsk_hndl
        );

    _hooks[ APP_CAPTIN ].setup_fnctn = nullptr;

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
        &_hooks[ APP_DEV ].tsk_hndl
        );

    _hooks[ APP_DEV ].setup_fnctn = nullptr;
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
        &_hooks[ APP_TICTACTOE ].tsk_hndl
        );

    _hooks[ APP_TICTACTOE ].setup_fnctn = TicTacToe_setup;
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
        &_hooks[ APP_SLOTMACHINE ].tsk_hndl
        );

    _hooks[ APP_SLOTMACHINE ].setup_fnctn = SlotMachine_setup;

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
        &_hooks[ APP_HACKER ].tsk_hndl
        );

    _hooks[ APP_HACKER ].setup_fnctn = Hacker_setup;
    return ERR_NONE;
}


/***************************************************
 * Init_Task_TouchTime()
 * 
 * Description: Create the Touch Time task
 **************************************************/
ct_err_t Init_Task_TouchTime( )
{
    xTaskCreate
        (
        TouchTime_run,
        "TouchTime",
        TASK_MIN_STACK,
        nullptr,
        tskMED_PRIORITY,
        &_hooks[ APP_TOUCHTIME ].tsk_hndl
        );

    _hooks[ APP_TOUCHTIME ].setup_fnctn = TouchTime_setup;
    return ERR_NONE;
}