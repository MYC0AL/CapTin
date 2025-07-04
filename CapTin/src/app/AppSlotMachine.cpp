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
static void Slot_InitReels( );
static void Slot_LoadReels( );
static void Slot_SpinReels( );
static void Slot_LockReels( );
static void Slot_UpdtItems( );
static void Slot_UpdtCoins( );

/**********************
 * Variables
 **********************/
static SlotReel_s reel[ REEL_CNT ] = {0};
static int        coins = 100;
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

    // https://github.com/h5n1xp/Arduino_Sprite?tab=readme-ov-file

    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    Arduino_GFX* canvas = Display_getCanvas();

    Display_getGFX()->fillScreen(BLACK); // Note: Do not call gfx->begin() when using canvas

    Slot_InitReels();

    uint8_t touch_count = 0;
    TP_Point touches[TOUCH_MAX] = {};

    while(1)
    {   
        Touch_getTouches( touches, &touch_count );

        if ( touch_count > 0 )
        {
            Slot_LoadReels();
        }

        Slot_SpinReels();
        Slot_LockReels();
        Slot_UpdtItems();
        Slot_UpdtCoins();
    }
}

/***************************************************
 * Slot_InitReels()
 * 
 * Description: Initialize the reels 
 **************************************************/
static void Slot_InitReels( )
{
    Serial.println("Initializing Reels");
    Arduino_GFX * canvas = Display_getCanvas();

    canvas->fillScreen(BLACK);

    for ( int i = 0; i < REEL_CNT; i++ )
    {
        reel[i].sprite = new Arduino_Sprite(128, 300, canvas);  /* Create a new sprite object              */
        reel[i].sprite->initAnim(1,0,0,128,1152);               /* Initialize the reel animation           */
        reel[i].sprite->begin((uint8_t*)imageReel,paletteReel); /* Initialize the sprites with their image */
        reel[i].sprite->Move((i*128)+(15*i)+15,0);              /* Move the reels into position            */
        reel[i].sprite->ScrollV();                              /* Scrolling here will draw the sprites    */
        reel[i].state = SLOT_STATE_LOAD;
    }

    canvas->flush();                                            /* Flushing the canvas will draw it         */
}

/***************************************************
 * Slot_LoadReels()
 * 
 * Description: Ready the reels for spinning
 **************************************************/
static void Slot_LoadReels( )
{
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state == SLOT_STATE_LOAD )
        {
            reel[i].scroll_tm = 85 - (i*15);
            reel[i].scroll_sp = 80 - (i*10);
            reel[i].state = SLOT_STATE_SPIN;
            //Serial.printf("Loaded Reel %d\r\n",i);
        }
    }
}

/***************************************************
 * Slot_SpinReels()
 * 
 * Description: Spin the reels
 **************************************************/
static void Slot_SpinReels( )
{
    //Serial.println("Spinning Reels");
    Arduino_GFX * canvas = Display_getCanvas();

    for (int i = 0; i < REEL_CNT; i++)
    {
        if ( reel[i].state == SLOT_STATE_SPIN )
        {
            if ( reel[i].scroll_tm > 0 )
            {
                reel[i].scroll = reel[i].scroll + reel[i].scroll_sp > 1152 ? 0 : reel[i].scroll + reel[i].scroll_sp;
                reel[i].sprite->Move(reel[i].sprite->GetX(),reel[i].scroll);
                reel[i].sprite->ScrollV();
                reel[i].scroll_tm--;
                reel[i].scroll_sp = reel[i].scroll_sp < 0 ? 0 : reel[i].scroll_sp - 1;
            }
            else
            {
                reel[i].state = SLOT_STATE_LOCK;
                //Serial.printf("Reel %d finished spinning, trans to lock\r\n",i);
            }
        }
    }

    canvas->flush();
}

/***************************************************
 * Slot_LockReels()
 * 
 * Description: After reels have spun, lock them
 *              in place.
 **************************************************/
static void Slot_LockReels( )
{
    //Serial.println("Locking Reels");
    /* Figure out displacement of each reel */
    /* If a reel is already locked, skip it */
    int reel_disp[ REEL_CNT ] = {0};
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state == SLOT_STATE_LOCK )
        {
            reel_disp[i] = reel[i].sprite->GetY() % REEL_WIDTH;
            if ( reel_disp[i] == 0 )
            {
                reel[i].state = SLOT_STATE_ITEM;
                //Serial.printf("Reel %d finished locking, trans to ITEM\r\n",i);
            }
        }
    }

    /* Process all reels ready for alignment */
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state == SLOT_STATE_LOCK )
        {
            int tmp_sp = reel_disp[i] > (REEL_WIDTH * 0.65) ? REEL_WIDTH - reel_disp[i] : -reel_disp[i];
            reel[i].scroll_sp = tmp_sp;
            reel[i].scroll_tm = 1;
            reel[i].state = SLOT_STATE_SPIN;
        }
    }
}

/***************************************************
 * Slot_UpdtItems()
 * 
 * Description: Update which item is selected on
 *              each reel.
 **************************************************/
static void Slot_UpdtItems( )
{
    //Serial.println("Updating reel items");
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state == SLOT_STATE_ITEM )
        {
            reel[i].item = reel[i].sprite->GetY() / REEL_WIDTH;
            reel[i].state = SLOT_STATE_COIN;
            //Serial.printf("Reel %d finished updating item, trans to COIN\r\n",i);
        }
    }
}

/***************************************************
 * Slot_UpdtCoins()
 * 
 * Description: Update user coin count
 **************************************************/
static void Slot_UpdtCoins( )
{
    /* Verify all reels are locked and their items are updated */
    bool rdy = true;
    for ( int i = 0; i < REEL_CNT & rdy; i++ )
    {
        if ( reel[i].state != SLOT_STATE_COIN )
        {
            rdy = false;
            return;
        }
    }

    //Serial.println("All reels ready, calculating winnings");

    /* Update coin count if win */
    for ( int i = 0; i < REEL_CNT & rdy; i++ )
    {
        reel[i].state = SLOT_STATE_LOAD;
    }

    coins++;

    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    gfx->setCursor(275,425);
    gfx->setTextSize(2);
    gfx->setTextColor(ORANGE);
    gfx->fillRect(275,425,160,20,BLACK);
    gfx->printf("Credits: %d",coins);
}