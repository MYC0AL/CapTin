/****************************************************
 * AppTicTacToe.cpp
 * 
 * The TicTacToe Application
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "app/AppTicTacToe.h"

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
 * TicTacToe_run()
 * 
 * Description: Run the TicTacToe application
 **************************************************/
void TicTacToe_run( void * pvParameters )
{
    Serial.println("TicTacToe: Application Started ");

    uint8_t touch_count = 0;
    TP_Point touches[TOUCH_MAX] = {};

    while( 1 )
    {
        Touch_getTouches( touches, &touch_count );
        if ( touch_count > 0 )
        {
            Serial.printf( "Touch Count: %d\r\n", touch_count );
            for ( int i = 0; i < touch_count; i++ )
            {
                Serial.printf( "Coord: (%d,%d)\r\n", touches[i].x, touches[i].y );
            }
            vTaskDelay(500);
        }
    }
}
