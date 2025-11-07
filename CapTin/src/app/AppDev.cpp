/****************************************************
 * AppDev.cpp
 * 
 * The Dev Application (for developers)
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "app/AppDev.h"
#include "cmn/DrawJPEG.h"
#include "cmn/ControlTouch.h"
#include "knl/TaskSetup.h"

/**********************
 * Defines
 **********************/

/**********************
 * Function Prototypes
 **********************/
static void ShowAllApps( );
static void StartApp( uint8_t app_idx );
static void StopApps( );

/**********************
 * Variables
 **********************/
BtnGUI_s DevAppBtns[ APP_COUNT ];
static char DevAppInitial[ APP_COUNT ] = { 'C', 'T', 'S', 'H' };
static bool DevEnabled = true;

/**********************
 * Functions
 **********************/

/***************************************************
 * Dev_run()
 * 
 * Description: Run the CapTin application
 **************************************************/
void Dev_run( void * pvParameters )
{
    Serial.println("Dev: Application Started ");

    ShowAllApps();

    while( 1 )
    {
        TP_Point tp[ TOUCH_MAX ];
        uint8_t touch_count = 0;
        Touch_getTouches( tp, &touch_count );

        if ( DevEnabled )
        {
            if ( touch_count )
            {
                for ( int i = 0; i < APP_COUNT; i ++ )
                {
                    if ( Touch_isBtnTouch( DevAppBtns[ i ], tp[ 0 ] ) == ERR_NONE )
                    {
                        /* Stop all apps */
                        StopApps();

                        /* Start desired app */
                        StartApp( i );
                        
                        DevEnabled = false;
                    }
                }
            }
        }
        else if ( touch_count == TOUCH_MAX )
        {
            StopApps();
            DevEnabled = true;
        }
    }
}

/***************************************************
 * ShowAllApps()
 * 
 * Description: Draw all applications
 **************************************************/
static void ShowAllApps( )
{
    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    gfx->fillScreen( BLACK );

    gfx->setTextColor( GOLD );
    gfx->setTextSize( 4 );
    gfx->setCursor( 0, 20 );
    gfx->printf( "====[ Dev Mode ]====" );
    gfx->setCursor( 0, gfx->height()-30 );
    gfx->printf( "====================" );

    /* Init the app buttons */
    memset( DevAppBtns, 0, sizeof( BtnGUI_s ) * APP_COUNT );
    for ( int i = 0; i < APP_COUNT; i++ )
    {
        DevAppBtns[ i ].x = (i % 3) * 140 + 50;
        DevAppBtns[ i ].y = (i / 3) * 140 + 100;
        DevAppBtns[ i ].w = 110;
        DevAppBtns[ i ].h = 110;
        DevAppBtns[ i ].c = GOLD;
    }

    /* Draw the buttons on the screen */
    for ( int i = 0; i < APP_COUNT; i++ )
    {
        gfx->drawRect( DevAppBtns[ i ].x, DevAppBtns[ i ].y, DevAppBtns[ i ].w, DevAppBtns[ i ].h, DevAppBtns[ i ].c );
        gfx->setCursor( DevAppBtns[ i ].x + 45, DevAppBtns[ i ].y + 35 );
        gfx->printf( "%c", DevAppInitial[ i ] );
    }
}

/***************************************************
 * StartApp()
 * 
 * Description: Start desired App
 **************************************************/
static void StartApp( uint8_t app_idx )
{
    /* Start the desired app */
    switch( app_idx )
    {
        case APP_CAPTIN:
            Init_Task_CapTin();
        break;

        case APP_TICTACTOE:
            Init_Task_TicTacToe();
        break;

        case APP_SLOTMACHINE:
            Init_Task_SlotMachine();
        break;

        case APP_HACKER:
            Init_Task_Hacker();
        break;
    }
}

/***************************************************
 * StartApp()
 * 
 * Description: Start desired App
 **************************************************/
static void StopApps( )
{
    /* Get a handle to each app */
    CapTin_Handles_t handles;
    GetCapTinHandles( handles );

    /* Stop all apps ( except Dev ) */
    for ( int i = 0; i < APP_COUNT; i++ )
    {
        if ( handles[ i ] != nullptr )
        {
            vTaskDelete( handles[ i ] );
        }
    }
}