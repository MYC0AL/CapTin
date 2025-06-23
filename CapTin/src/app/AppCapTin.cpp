/****************************************************
 * AppCapTin.cpp
 * 
 * The CapTin Application
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "app/AppCapTin.h"
#include "cmn/DrawJPEG.h"

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
 * CapTin_run()
 * 
 * Description: Run the CapTin application
 **************************************************/
void CapTin_run( void * pvParameters )
{
    Serial.println("CapTin: Application Started ");

    // const char * file_name = "/golden.jpg";
    // Display_FillJPEG( file_name );

    while( 1 )
    {
        // Serial.println( "CapTin: Heartbeat" );
        vTaskDelay( 1000 );
    }
}
