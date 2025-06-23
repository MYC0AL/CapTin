/****************************************************
 * ControlTouch.cpp
 * 
 * Control the TAMC_GT911 Touch Library
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "cmn/ControlTouch.h"

/**********************
 * Defines
 **********************/

/**********************
 * Types
 **********************/

/**********************
 * Variables
 **********************/
TAMC_GT911 ts = TAMC_GT911(I2C_SDA_PIN, I2C_SCL_PIN, TOUCH_INT, TOUCH_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

/**********************
 * Functions
 **********************/

/***************************************************
 * Touch_getDriver()
 * 
 * @brief Get the Touch Driver object.
 **************************************************/
TAMC_GT911* Touch_getDriver( )
{
    return &ts;
}

ct_err_t Touch_getTouches( TP_Point touches[TOUCH_MAX], uint8_t* touch_count )
{
    /* Read the TAMC_GT911 for touch information */
    ts.read();

    /* Set the touch count */
    *touch_count = ts.touches;

    for (uint8_t i = 0; i < *touch_count && (i < TOUCH_MAX); ++i)
    {
        touches[i].x = map(ts.points[i].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, 480 - 1);
        touches[i].y = map(ts.points[i].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, 480 - 1);
    }

    //ts.isTouched = false
    return ERR_NONE;
}
