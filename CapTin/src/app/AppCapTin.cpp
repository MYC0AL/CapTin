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

    while( 1 )
    {
        Serial.println("CapTin: Heartbeat");
        vTaskDelay( 1000 );
    }
}
