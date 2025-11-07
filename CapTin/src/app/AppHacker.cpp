/****************************************************
 * AppHacker.cpp
 * 
 * The Hacker Application
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "app/AppHacker.h"

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
 * Hacker_run()
 * 
 * Description: Run the Hacker Application
 **************************************************/
void Hacker_run( void * pvParameters )
{
    Serial.println("Hacker: Application Started ");

    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    Arduino_GFX* canvas = Display_getCanvas();

    char data[15][15];

    /* Initialize the screen to clear black */
    gfx->fillScreen( BLACK );

    LeetLine line( gfx );

    gfx->setTextSize( 3 );

    while( 1 )
        {
        for( int i = 0; i < 15; i++ )
        {
            for( int j = 0; j < 15; j++ )
            {
            data[i][j] = (rand() % 126) + 32;
            }
        }
        gfx->setCursor(0,0);
        gfx->setTextColor( GREEN );
        for( int i = 0; i < 15; i++ )
            {             
            for( int j = 0; j < 15; j++ )
                {
                gfx->printf("%c", data[i][j]);
                }
            gfx->printf("\n");
            }
        gfx->setCursor(0,0);
        gfx->setTextColor( BLACK );
        for( int i = 0; i < 15; i++ )
            {             
            for( int j = 0; j < 15; j++ )
                {
                gfx->printf("%c", data[i][j]);
                }
            gfx->printf("\n");
            }
        }
}

LeetLine::LeetLine( Arduino_ST7701_RGBPanel * gfx )
{
    const uint32_t LEET_COLORS[] = { GREEN, DARKGREEN, LIGHTGREEN };
    _gfx = gfx;
    _text_size = ( rand() % LEET_LINE_TEXT_SIZE_MAX ) + 1;
    _height = ( rand() % LEET_LINE_MAX_HEIGHT ) + LEET_LINE_MIN_HEIGHT;
    _color = LEET_COLORS[( rand() % 3 )];

    for( int i = 0; i < _height; i++ )
    {
        _line[ i ] = ( rand() % 26 ) + 65;
    }
}

/***************************************************
 * UpdateLine()
 * 
 * Description: Helper function to update a new line
 **************************************************/
void LeetLine::UpdateLine()
{
    uint8_t update_factor = rand() % 26;
    for( int i = 0; i < _height; i++ )
    {
        _last_line[ i ] = _line[ i ];
        _line[ i ] = ((_line[ i ] + update_factor) % 26) + 65;
    }
}

/***************************************************
 * DisplayLine()
 * 
 * Description: Helper function to display line
 **************************************************/
void LeetLine::DisplayLine()
{

    /* Setup this lines config */
    _gfx->setTextSize( _text_size );

    /* Clear old line */
    _gfx->setTextColor( BLACK );
    _gfx->setCursor( 0, 100 );
    for( int i = 0; i < _height; i++ )
    {
        _gfx->printf( "%c\n", _last_line[ i ] );
    }

    /* Draw new line */
    _gfx->setCursor( 0, 100 );
    _gfx->setTextColor( _color );
    for( int i = 0; i < _height; i++ )
    {
        _gfx->printf( "%c\n", _line[ i ] );
        vTaskDelay( 25 );
    }

}
