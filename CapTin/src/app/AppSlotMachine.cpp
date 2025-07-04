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

static void DisplayUI( );
static void IncBetAmnt( );
static void DecBetAmnt( );


/**********************
 * Variables
 **********************/
static SlotReel_s reel[ REEL_CNT ] = {0};
static int        coins = 100;
static uint8_t    bet_amnt = 1;

static BtnGUI_s   btn_bet_add = { .x = 30, .y = 410, .w = 50, .h = 50, .c = GREEN };
static BtnGUI_s   btn_bet_sub = { .x = 225, .y = 410, .w = 50, .h = 50, .c = RED };

static bool       gui_locked = false;

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
    DisplayUI();

    uint8_t touch_count = 0;
    TP_Point touches[TOUCH_MAX] = {};

    while(1)
    {   
        Touch_getTouches( touches, &touch_count );

        if ( touch_count > 0 )
        {
            /* Check if touches were a button press */
            if ( Touch_isBtnTouch( btn_bet_add, touches[0] ) == ERR_NONE )
            {
                IncBetAmnt( );
            }
            else if ( Touch_isBtnTouch( btn_bet_sub, touches[0] ) == ERR_NONE )
            {
                DecBetAmnt( );
            }
            else
            {
                Slot_LoadReels();
            }
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
    /* Verify enough coins to play slots */
    if ( coins - bet_amnt >= 0 )
    {
        for ( int i = 0; i < REEL_CNT; i++ )
        {
            if ( reel[i].state == SLOT_STATE_LOAD)
            {
                reel[i].scroll_tm = 85 - (i*15);
                reel[i].scroll_sp = 80 - (i*10);
                reel[i].state = SLOT_STATE_SPIN;

                gui_locked = true;
            }
        }

        coins -= bet_amnt;
        DisplayUI();
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
            }
        }
    }

    /* Process all reels ready for alignment */
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state == SLOT_STATE_LOCK )
        {
            int tmp_sp = reel_disp[i] > (REEL_WIDTH * 0.45) ? REEL_WIDTH - reel_disp[i] : -reel_disp[i];
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
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state == SLOT_STATE_ITEM )
        {
            reel[i].item = reel[i].sprite->GetY() / REEL_WIDTH;
            reel[i].state = SLOT_STATE_COIN;
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

    /* Update coin count if win */
    coins++;

    /* Reset reels to load state */
    for ( int i = 0; i < REEL_CNT & rdy; i++ )
    {
        reel[i].state = SLOT_STATE_LOAD;
    }

    /* Animation over, unlock gui */
    gui_locked = false;

    DisplayUI();
}

/***************************************************
 * DisplayCoins()
 * 
 * Description: Display current coin count
 **************************************************/
static void DisplayUI( )
{
    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    gfx->setCursor(305,410);
    gfx->setTextSize(2);
    gfx->setTextColor(ORANGE);
    gfx->fillRect(305,410,160,20,BLACK);
    gfx->printf("Credits: %d",coins);

    /* Display bet amount text and buttons */
    gfx->fillRect( btn_bet_add.x, btn_bet_add.y, btn_bet_add.w, btn_bet_add.h, btn_bet_add.c );
    gfx->fillRect( btn_bet_sub.x, btn_bet_sub.y, btn_bet_sub.w, btn_bet_sub.h, btn_bet_sub.c );

    gfx->setTextSize(2);
    gfx->setCursor( 110, 410 );
    gfx->setTextColor( GREEN );
    gfx->fillRect( 110, 410, 90, 20, BLACK );
    gfx->printf( "Bet: %d",bet_amnt );

}

/***************************************************
 * IncBetAmnt()
 * 
 * Description: Increase bet amount
 **************************************************/
static void IncBetAmnt( )
{
    if ( !gui_locked )
    {
        bet_amnt += bet_amnt >= coins ? 0 : 1; 
        DisplayUI();
        vTaskDelay( 1500 );
    }
}

/***************************************************
 * DecBetAmnt()
 * 
 * Description: Decrease bet amount
 **************************************************/
static void DecBetAmnt( )
{
    if ( !gui_locked )
    {
        bet_amnt -= bet_amnt == 0 ? 0 : 1; 
        DisplayUI();
        vTaskDelay( 1500 );
    }
}