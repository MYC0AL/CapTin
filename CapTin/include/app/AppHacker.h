/****************************************************
 * AppHacker.h
 * 
 * The Hacker Application
 * 
 ****************************************************/
#pragma once

/**********************
 * Includes
 **********************/
#include "cmn/Errors.h"
#include <FreeRTOS.h>
#include "cmn/ControlDisplay.h"
#include "cmn/ControlTouch.h"

/**********************
 * Defines
 **********************/
#define LEET_LINE_MAX_HEIGHT        10
#define LEET_LINE_MIN_HEIGHT        4             
#define LEET_LINE_TEXT_SIZE_MAX     5
/**********************
 * Function Prototypes
 **********************/

/**********************
 * Variables
 **********************/

/**********************
 * Classes
 **********************/
class LeetLine
    {
    public:
    LeetLine( Arduino_ST7701_RGBPanel * gfx );
    void UpdateLine();
    void DisplayLine();

    private:
    char _line[ LEET_LINE_MAX_HEIGHT ];
    char _last_line[ LEET_LINE_MAX_HEIGHT ];
    uint8_t _height;
    uint8_t _text_size;
    uint32_t _color;
    uint16_t _x_pos;
    uint16_t _y_pos;
    Arduino_ST7701_RGBPanel * _gfx;
    };

/**********************
 * Functions
 **********************/
void Hacker_run( void * pvParameters );

