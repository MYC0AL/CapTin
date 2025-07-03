/****************************************************
 * AppSlotMachine.cpp
 * 
 * The Slot Machine Application
 * 
 ****************************************************/

/**********************
 * Includes
 **********************/
#include "app/AppSlotMachine.h"

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
 * SlotMachine_run()
 * 
 * Description: Run the Slot Machine application
 **************************************************/
void SlotMachine_run( void * pvParameters )
{
    Serial.println("SlotMachine: Application Started ");

    // TODO MJB: Use https://github.com/h5n1xp/Arduino_Sprite?tab=readme-ov-file ?

    int aAframe = 0;
    int scroll = 0;
    Arduino_Sprite* a;

    Arduino_Sprite* reel1;
    Arduino_Sprite* reel2;
    Arduino_Sprite* reel3;

    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();

    Arduino_GFX* canvas = Display_getCanvas();

    canvas->fillScreen(BLACK);
    canvas->flush();

    Display_getGFX()->fillScreen(BLACK); // Note: Do not call gfx->begin() when using canvas

    reel1 = new Arduino_Sprite(128, 300, canvas);
    reel1->Move(15,0);
    reel1->begin((uint8_t*)imageReel,paletteReel);
    reel1->initAnim(1,0,0,128,1152);

    reel2 = new Arduino_Sprite(128, 300, canvas);
    reel2->Move(15+128+15,0);
    reel2->begin((uint8_t*)imageReel,paletteReel);
    reel2->initAnim(1,0,0,128,1152);

    reel3 = new Arduino_Sprite(128, 300, canvas);
    reel3->Move(15+128+15+128+15,0);
    reel3->begin((uint8_t*)imageReel,paletteReel);
    reel3->initAnim(1,0,0,128,1152);

    while(1)
    {
        scroll += 30;

        if( scroll > 1152 )
        {
            scroll = 0;
        }
        
        reel1->Move(15,scroll);
        reel1->ScrollV();

        reel2->Move(15+128+15,scroll);
        reel2->ScrollV();

        reel3->Move(15+128+15+128+15,scroll);
        reel3->ScrollV();

        //reel1->Frame(aAframe);
        // reel2->Frame(aAframe);
        //reel3->Frame(aAframe);


        //reel1->Draw();
        // reel2->Draw();
        //reel3->Draw();

        canvas->flush();
        //gfx->print("test");
    }
}