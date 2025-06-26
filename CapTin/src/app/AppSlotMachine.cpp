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
    int scrollM = 0;
    Arduino_Sprite* a;
    Arduino_Sprite* foreground;
    Arduino_Sprite* dog;

    Arduino_GFX *canvas = new Arduino_Canvas( 480, 480, Display_getGFX(), 0, 0 );
    canvas->begin();

    canvas->fillScreen(LIGHTGREY);
    canvas->flush();
    Display_getGFX()->fillScreen(RED); // Note: Do not call gfx->begin() when using canvas

    // foreground = new Arduino_Sprite(320,73,canvas);
    // foreground->begin((uint8_t*)imageM,paletteM);
    // foreground->SetChromaKey(0x0);

    dog = new Arduino_Sprite(225, 225, canvas);
    dog->begin((uint8_t*)myBitmapsprite_dog,0);
    dog->SetChromaKey(0x0);

    a = new Arduino_Sprite(240,50,canvas);
    a->begin((uint8_t*)imageA,paletteA);
    a->SetChromaKey(0x0);
    a->Move(130, 94);
    a->initAnim(5,0,0,40,50);
    a->SetBackingStore();

    while(1)
    {
        a->Clear();

        //foreground->Clear();

        // Foreground
        // scrollM -= 3;

        // if(scrollM < 0)
        // {
        //     scrollM = 320 + scrollM;
        // }

        // foreground->Move(scrollM,67);
        // foreground->Scroll();

        //Main player
        aAframe += 1;

        if(aAframe > 5)
        {
            aAframe = 0;
        }

        a->Frame(aAframe);
        a->Draw();

        dog->Draw();

        canvas->flush();
    }
}