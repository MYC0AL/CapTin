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
    Arduino_Sprite* a;
    Arduino_Sprite* foreground;
    Arduino_Sprite* man;

    Arduino_GFX* canvas = Display_getCanvas();

    canvas->fillScreen(LIGHTGREY);
    canvas->flush();

    Display_getGFX()->fillScreen(RED); // Note: Do not call gfx->begin() when using canvas

    a = new Arduino_Sprite(240,50,canvas);
    a->begin((uint8_t*)imageA,paletteA);
    a->SetChromaKey(0x0);
    a->Move(130, 94);
    a->initAnim(5,0,0,40,50);
    a->SetBackingStore();

    man = new Arduino_Sprite(384, 64, canvas);
    man->begin((uint8_t*)imageMan,paletteMan);
    man->SetChromaKey(0x0);
    man->Move(10,200);
    man->initAnim(5,0,0,128,128);
    man->SetBackingStore();

    while(1)
    {
        a->Clear();
        man->Clear();

        //Main player
        aAframe += 1;

        if(aAframe > 5)
        {
            aAframe = 0;
        }

        a->Frame(aAframe);
        a->Draw();

        man->Frame(aAframe);
        man->Draw();

        canvas->flush();
    }
}