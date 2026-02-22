/****************************************************
 * AppTouchTime.cpp
 * 
 * The TouchTime Application
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "app/AppTouchTime.h"

/**********************
 * Defines
 **********************/

/**********************
 * Function Prototypes
 **********************/
static void TT_StartGame( TouchTimeGames_t game );

/**********************
 * Variables
 **********************/
static TouchTimeGames_t s_tt_game;
static AvoidObsticles s_avd_obstcl;

/**********************
 * Functions
 **********************/

 /***************************************************
 * TouchTime_setup()
 * 
 * Description: Setup the TouchTime app
 **************************************************/
void TouchTime_setup( )
{
    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    gfx->fillScreen( BLACK );
    gfx->setTextSize( 3 );

    gfx->printf( "Touch to Start" );
    gfx->setCursor( gfx->width() / 2 - 50, gfx->height() / 2 );

    /* Initialize variables */
    s_tt_game = TT_GAME_NONE;
}

/***************************************************
 * TouchTime_run()
 * 
 * Description: Run the TouchTime Application
 **************************************************/
void TouchTime_run( void * pvParameters )
{
    Serial.println("TouchTime: Application Started ");

    /* Suspend self on startup */
    vTaskSuspend( NULL );

    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    Arduino_GFX* canvas = Display_getCanvas();

    uint8_t touch_count = 0;
    TP_Point touches[TOUCH_MAX] = {};

    ntfy_app_t8 tsk_notifs = NTFY_NONE;

    while( 1 )
    {
        /* Check task notifications */
        xTaskNotifyWait( 0, 0, &tsk_notifs, 0 );

        switch( tsk_notifs )
        {
            case NTFY_SETUP:
                TouchTime_setup();

                /* Wait a little while transition to avoid initial touches */
                vTaskDelay( pdMS_TO_TICKS( 500 ) );
            break;

            case NTFY_PRDC:
               /* Handle task periodics */
                Touch_getTouches( touches, &touch_count );

                if ( s_tt_game == TT_GAME_NONE )
                {
                    if ( touch_count > 0 )
                    {
                        TT_StartGame( TT_GAME_AO );
                    }
                }
                
                vTaskDelay( pdMS_TO_TICKS( 10 ) );
            break;
        }
    }
}

 /***************************************************
 * TT_StartGame()
 * 
 * Description: Start a Touch Time game
 **************************************************/
void TT_StartGame( TouchTimeGames_t game )
{
    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    cursor_config( 100, 200, 3, GREEN );

    gfx->fillScreen( BLACK );
    gfx->printf( "Loading Game..." );
    vTaskDelay( pdMS_TO_TICKS( 1500 ) );

    switch( game )
    {
        case TT_GAME_AO:
            s_avd_obstcl.Start();
        break;
    }
}

 /***************************************************
 * AvoidObsticles()
 * 
 * Description: AvoidObsticles ctor
 **************************************************/
AvoidObsticles::AvoidObsticles()
{
    m_state = TT_AO_IDLE;
    m_level = 0;
    memset( m_obsticles, 0, sizeof( ObsticleAttr_s ) * AO_OBSTCLS_MAX );
    memset( &m_player, 0, sizeof( ObsticleAttr_s ) );
}

 /***************************************************
 * AvoidObsticles::Start()
 * 
 * Description: Start the AvoidObsticles game
 **************************************************/
void AvoidObsticles::Start( )
{
Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
gfx->fillScreen( BLACK );
}

 /***************************************************
 * AvoidObsticles::Pause()
 * 
 * Description: Pause the AvoidObsticles game
 **************************************************/
void AvoidObsticles::Pause( )
{

}

 /***************************************************
 * AvoidObsticles::UpdateFrame()
 * 
 * Description: Update the frame
 **************************************************/
void AvoidObsticles::UpdateFrame( )
{

}