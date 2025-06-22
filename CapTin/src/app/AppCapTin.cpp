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
#include <Arduino_GFX_Library.h>

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
extern int jpegDrawCallback(JPEGDRAW *pDraw);

//TODO MJB: Remove this once we get NFC working

/***************************************************
 * CapTin_run()
 * 
 * Description: 
 **************************************************/
void CapTin_run( void * pvParameters )
{
    Serial.println("CapTin: Application Started ");

    const char * file_name = "/golden.jpg";
    Display_FillJPEG( file_name );

    uint8_t touch_count = 0;
    TP_Point touches[TOUCH_MAX] = {};

    while( 1 )
    {
        Touch_getTouches( touches, &touch_count );
        Serial.printf( "Touch Count: %d\r\n", touch_count );
        for ( int i = 0; i < touch_count; i++ )
        {
            Serial.printf( "Coord: (%d,%d)\r\n", touches[i].x, touches[i].y );
        }
        vTaskDelay( 1000 );
    }
}
