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

    Display_getCanvas()->fillScreen(LIGHTGREY);
    Display_getCanvas()->flush();

    Display_getGFX()->fillScreen(RED); // Note: Do not call gfx->begin() when using canvas

    a = new Arduino_Sprite(240,50,Display_getCanvas());
    a->begin((uint8_t*)imageA,paletteA);
    a->SetChromaKey(0x0);
    a->Move(130, 94);
    a->initAnim(5,0,0,40,50);
    a->SetBackingStore();

    while(1)
    {
        a->Clear();

        //Main player
        aAframe += 1;

        if(aAframe > 5)
        {
            aAframe = 0;
        }

        a->Frame(aAframe);
        a->Draw();

        Display_getCanvas()->flush();
    }
}