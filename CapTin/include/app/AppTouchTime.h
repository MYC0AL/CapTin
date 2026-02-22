/****************************************************
 * AppTouchTime.h
 * 
 * The TouchTime Application
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
#include "knl/TaskSetup.h"

/**********************
 * Defines
 **********************/
#define AO_OBSTCLS_MAX 10

/**********************
 * Types
 **********************/
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint16_t color;
    uint16_t velocity;
} ObsticleAttr_s;

/* State of AvoidObsticle */
typedef uint8_t AvoidState_t;
enum
{
    TT_AO_IDLE,
    TT_AO_START,
    TT_AO_PAUSE,
    TT_AO_END
};

/* All supported Touch Time games */
typedef uint8_t TouchTimeGames_t;
enum
    {
    TT_GAME_NONE,

    TT_GAME_AO,

    TT_GAME_LAST = TT_GAME_AO,
    TT_GAME_CNT = TT_GAME_LAST + 1,
    };

/**********************
 * Function Prototypes
 **********************/

/**********************
 * Variables
 **********************/

/**********************
 * Classes
 **********************/
class AvoidObsticles
{
public:
    AvoidObsticles();
    void Start( );
    void Pause( );
    void UpdateFrame( );

private:
    AvoidState_t m_state;
    uint8_t m_level;
    ObsticleAttr_s m_obsticles[ AO_OBSTCLS_MAX ];
    ObsticleAttr_s m_player;

    void generateObsticles();

};

/**********************
 * Functions
 **********************/
void TouchTime_setup( );
void TouchTime_run( void * pvParameters );

