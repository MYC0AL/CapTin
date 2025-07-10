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
static void Slot_UpdtCoins( );

static void DisplayUI( );
static void IncBetAmnt( );
static void DecBetAmnt( );
static SlotWins_t GetSlotWin();
static SlotItems_t MapWinToItem( SlotWins_t win, uint8_t &payout );


/**********************
 * Variables
 **********************/
static SlotReel_s  reel[ REEL_CNT ] = {0};
static int         coins = 100;
static int         bet_amnt = 1;
static SlotWins_t  curr_win = SLOT_WIN_NONE;
static SlotItems_t curr_item = SLOT_ITEM_SEVEN;
static uint8_t     curr_payout = 0;

static BtnGUI_s   btn_bet_add = { .x = 7, .y = 370, .w = 60, .h = 100, .c = GREEN };
static BtnGUI_s   btn_bet_sub = { .x = 180, .y = 370, .w = 60, .h = 100, .c = RED };
static BtnGUI_s   btn_spin_reel = { .x = 20, .y = 90, .w = 440, .h = 256, .c = LIGHTBLACK };
//440, 256, gfx, 20, 90
static bool       gui_locked = false;

static int        seed = 0;

static double SlotWinPrbblty[ SLOT_WIN_COUNT ] = 
{
/* Probability:    Return:          Item Shown:                     Name:  */
    0.60,         /* 0x bet   */    /* Random 3 different items */   /* SLOT_WIN_NONE */
    0.30,         /* 1x bet   */    /* Cherry, Lemon            */   /* SLOT_WIN_SMLL */
    0.055,        /* 3x bet   */    /* Orange, Banana           */   /* SLOT_WIN_LRGE */
    0.025,        /* 5x bet   */    /* Watermelon, Grape        */   /* SLOT_WIN_MNOR */
    0.015,        /* 10x bet  */    /* Bell, Bar                */   /* SLOT_WIN_MJOR */
    0.005,        /* 50x bet  */    /* Seven                    */   /* SLOT_WIN_JKPT */
};

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

    /* Draw background picture */
    const char * file_name = "/slot_machine.jpg";
    Display_FillJPEG( file_name );

    Slot_InitReels();
    DisplayUI();

    uint8_t touch_count = 0;
    TP_Point touches[TOUCH_MAX] = {};

    while(1)
    {   
        Touch_getTouches( touches, &touch_count );

        if ( touch_count > 0 )
        {
            /* Update seed */
            srand(touches[0].x * touches[0].y);

            /* Check if touches were a button press */
            if ( Touch_isBtnTouch( btn_bet_add, touches[0] ) == ERR_NONE )
            {
                IncBetAmnt( );
            }
            else if ( Touch_isBtnTouch( btn_bet_sub, touches[0] ) == ERR_NONE )
            {
                DecBetAmnt( );
            }
            else if ( Touch_isBtnTouch( btn_spin_reel, touches[0] ) == ERR_NONE )
            {
                Slot_LoadReels();
            }
        }

        Slot_SpinReels();
    }
}

/***************************************************
 * Slot_InitReels()
 * 
 * Description: Initialize the reels 
 **************************************************/
static void Slot_InitReels( )
{
    Arduino_GFX * canvas = Display_getCanvas();

    canvas->fillScreen( LIGHTBLACK );

    for ( int i = 0; i < REEL_CNT; i++ )
    {
        reel[i].sprite = new Arduino_Sprite(128, 300, canvas);  /* Create a new sprite object              */
        reel[i].sprite->initAnim(0,0,0,128,1152);               /* Initialize the reel animation           */
        reel[i].sprite->begin((uint8_t*)imageReel,paletteReel); /* Initialize the sprites with their image */
        reel[i].sprite->Move((i*128)+(15*i)+15,ITEM_HEIGHT/2);              /* Move the reels into position            */
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
    if ( coins - bet_amnt >= 0 && !gui_locked )
    {
        curr_win = GetSlotWin();
        curr_payout = 0;

        if ( curr_win != SLOT_WIN_NONE )
        {
            curr_item = MapWinToItem( curr_win, curr_payout );
            reel[0].item = curr_item;
            reel[1].item = curr_item;
            reel[2].item = curr_item;
        }
        else
        {
            reel[2].item = (rand() % SLOT_ITEM_COUNT);
            reel[1].item = (reel[0].item + rand()) % SLOT_ITEM_COUNT;
            reel[0].item = reel[2].item == reel[1].item ? (reel[2].item + 1) % SLOT_ITEM_COUNT : (rand() % SLOT_ITEM_COUNT);
        }

        for ( int i = 0; i < REEL_CNT; i++ )
        {
            if ( reel[i].state == SLOT_STATE_LOAD)
            {
                reel[i].scroll_sp = 70 - (i*10);
                reel[i].state = SLOT_STATE_SPIN;

                int dist_to_item = 
                    ( (SLOT_ITEM_COUNT - reel[i].item + 1) * ITEM_HEIGHT - reel[i].scroll + REEL_HEIGHT )
                     % REEL_HEIGHT - ITEM_HEIGHT / 2;
                reel[i].scroll_pxl = (4 - i) * (REEL_HEIGHT) + dist_to_item;

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
    Arduino_GFX * canvas = Display_getCanvas();

    static uint8_t stp_reel_cnt = 0;

    for (int i = 0; i < REEL_CNT; i++)
    {
        /* Ensure each reel is in the proper state */
        if ( reel[i].state == SLOT_STATE_SPIN )
        {
            /* Slowdown the reel when getting close to end */
            if ( reel[i].scroll_pxl <= 256 )
            {
                const uint8_t slowdown_speed = 30;
                reel[i].scroll_sp = reel[i].scroll_pxl - slowdown_speed <= 0 ? reel[i].scroll_pxl : slowdown_speed;
            }

            /* Check if each reel has more pixels to move */
            if ( reel[i].scroll_pxl > 0 )       
            {
                reel[i].scroll = (reel[i].scroll + reel[i].scroll_sp) % REEL_HEIGHT;
                reel[i].sprite->Move(reel[i].sprite->GetX(),reel[i].scroll);
                reel[i].sprite->ScrollV();
                reel[i].scroll_pxl -= reel[i].scroll_sp;
            }
            else
            {
                /* This reel has stopped, move it to the next state */
                reel[i].state = SLOT_STATE_COIN;
                stp_reel_cnt++;
            }
        }
    }

    canvas->flush();

    /* All reels have finished, update coins */
    if ( stp_reel_cnt == REEL_CNT )
    {
        stp_reel_cnt = 0;
        Slot_UpdtCoins( );
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
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        if ( reel[i].state != SLOT_STATE_COIN )
        {
            return;
        }
    }

    /* Update coin count if win */
    coins += (bet_amnt * curr_payout);

    /* Reset reels to load state */
    for ( int i = 0; i < REEL_CNT; i++ )
    {
        reel[i].state = SLOT_STATE_LOAD;
    }

    /* Animation over, unlock gui */
    gui_locked = false;

    DisplayUI();
}

/***************************************************
 * DisplayUI()
 * 
 * Description: Display current GUI count
 **************************************************/
static void DisplayUI( )
{
    Arduino_ST7701_RGBPanel * gfx = Display_getGFX();
    gfx->setCursor( 325, 415 );
    gfx->setTextSize( 3 );
    gfx->setTextColor( GOLD );
    gfx->fillRect( 325, 415, 90, 25, LIGHTBLACK );
    gfx->printf( "%d",coins );

    /* Display bet amount text and buttons */
    //gfx->drawRect( btn_bet_add.x, btn_bet_add.y, btn_bet_add.w, btn_bet_add.h, btn_bet_add.c );
    //gfx->drawRect( btn_bet_sub.x, btn_bet_sub.y, btn_bet_sub.w, btn_bet_sub.h, btn_bet_sub.c );

    gfx->setTextSize( 3 );
    gfx->setCursor( 100, 415 );
    gfx->setTextColor( GOLD );
    gfx->fillRect( 100, 415, 70, 25, LIGHTBLACK );
    gfx->printf( "%d",bet_amnt );

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
        bet_amnt = bet_amnt > 9999 ? 9999 : bet_amnt;
        DisplayUI();
        vTaskDelay( 350 );
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
        bet_amnt = bet_amnt == 0 ? min(coins,9999) : bet_amnt - 1;
        DisplayUI();
        vTaskDelay( 350 );
    }
}

/***************************************************
 * GetSlotWin()
 * 
 * Description: Determine a win for this round
 **************************************************/
static SlotWins_t GetSlotWin()
{
    double rndm = rand() / ( RAND_MAX + 1.0 );
    double cumulative = 0.0;

    for ( int i = 0; i < SLOT_WIN_COUNT; ++i )
    {
        cumulative += SlotWinPrbblty[ i ];
        if ( rndm < cumulative ) 
        {
            return i;
        }
    }

    /* Fallback loss */
    return (0);

}

/***************************************************
 * MapWinToItem()
 * 
 * Description: Map an item to a win
 **************************************************/
static SlotItems_t MapWinToItem( SlotWins_t win, uint8_t &payout )
{
    SlotItems_t ret_val = SLOT_ITEM_CHERRY;

    switch( win )
    {
        case SLOT_WIN_JKPT:
            ret_val = SLOT_ITEM_SEVEN;
            payout = 50;
            break;

        case SLOT_WIN_MJOR:
            ret_val = (rand() % 2) == 0 ? SLOT_ITEM_CHERRY : SLOT_ITEM_LEMON;
            payout = 10;
            break;

        case SLOT_WIN_MNOR:
            ret_val = (rand() % 2) == 0 ? SLOT_ITEM_MELON : SLOT_ITEM_GRAPE;
            payout = 5;
            break;

        case SLOT_WIN_LRGE:
            ret_val = (rand() % 2) == 0 ? SLOT_ITEM_ORANGE : SLOT_ITEM_BANANA;
            payout = 3;
            break;

        case SLOT_WIN_SMLL:
            ret_val = (rand() % 2) == 0 ? SLOT_ITEM_CHERRY : SLOT_ITEM_LEMON;
            payout = 1;
            break;

        default:
            ret_val = SLOT_ITEM_CHERRY;
            payout = 0;
    }

    return ret_val;
}