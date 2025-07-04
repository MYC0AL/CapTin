/****************************************************
 * SlotMachine.h
 * 
 * The Slot Machine Application
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
#include "arduino_sprite.h"
#include "sprites/reel.h"
#include <stdlib.h>
#include <iostream>

/**********************
 * Defines
 **********************/
#define REEL_CNT    3
#define REEL_WIDTH  128
#define SLOT_MID    150

/**********************
 * Types
 **********************/
typedef enum
{
    SLOT_STATE_IDLE,
    SLOT_STATE_LOAD,
    SLOT_STATE_SPIN,
    SLOT_STATE_LOCK,
    SLOT_STATE_ITEM,
    SLOT_STATE_COIN,
} SlotState_t;

typedef uint8_t SlotItems_t;
enum 
{
    SLOT_ITEM_SEVEN = 0,
    SLOT_ITEM_BELL,
    SLOT_ITEM_ORANGE,
    SLOT_ITEM_BANNANA,
    SLOT_ITEM_BAR,
    SLOT_ITEM_GRAPE,
    SLOT_ITEM_MELON,
    SLOT_ITEM_LEMON,
    SLOT_ITEM_CHERRY
};

typedef struct
{
    Arduino_Sprite* sprite;
    int             scroll;     /* How far the sprite has scrolled */
    int             scroll_sp;  /* How fast the sprite scrolls     */
    uint8_t         scroll_tm;  /* How long the sprite scrolls     */
    SlotState_t     state;      /* State the reel is in            */
    SlotItems_t     item;       /* Currently selected item         */

} SlotReel_s;

/**********************
 * Variables
**********************/

/**********************
 * Functions
 **********************/
void SlotMachine_run( void * pvParameters );

/**********************
 * Classes
 **********************/
