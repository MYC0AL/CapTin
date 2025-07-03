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

    canvas->fillScreen(DARKGREY);
    canvas->flush();

    // gfx->setCursor(10,410);
    // gfx->setTextSize(3);
    // gfx->setTextColor(RED);
    // gfx->print("test");

    Display_getGFX()->fillScreen(BLUE); // Note: Do not call gfx->begin() when using canvas

    // a = new Arduino_Sprite(240,50,canvas);
    // a->begin((uint8_t*)imageA,paletteA);
    // a->SetChromaKey(0x0);
    // a->Move(130, 94);
    // a->initAnim(5,0,0,40,50);
    // a->SetBackingStore();

    reel1 = new Arduino_Sprite(128, 1152, canvas);
    //reel1->SetChromaKey(0x0);
    //reel1->Move(15,15);
    reel1->initAnim(9,0,900,128,300);
    reel1->begin((uint8_t*)imageReel,paletteReel);
    //reel1->SetBackingStore();

    // reel2 = new Arduino_Sprite(384, 64, canvas);
    // reel2->begin((uint8_t*)imageMan,paletteMan);
    // reel2->SetChromaKey(0x0);
    // reel2->Move(15,15+128);
    // reel2->initAnim(5,0,0,128,128);
    // reel2->SetBackingStore();

    // reel3 = new Arduino_Sprite(384, 64, canvas);
    // reel3->Move(345,176);
    // reel3->initAnim(0,0,0,128,128);
    // reel3->begin((uint8_t*)imageMan,paletteMan);

    while(1)
    {
        //reel1->Clear();
        // reel2->Clear();
        // reel3->Clear();

        //Main player
        // aAframe += 1;

        // if(aAframe > 8)
        // {
        //     aAframe = 0;
        // }

        scroll -= 5;

        if( scroll < 0 )
        {
            scroll = 900;
        }
        
        reel1->Move(15,scroll);
        reel1->Scroll();

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