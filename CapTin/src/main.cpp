
#include "cmn/DrawJPEG.h"
#include "cmn/ControlSD.h"
#include "cmn/ControlDisplay.h"
#include "cmn/ControlTouch.h"
#include "knl/TaskSetup.h"
#include "cmn/Config.h"

void setup()
{

  Serial.begin(9600);

  Touch_getDriver()->begin();
  Serial.println("CapTin: Touch Driver Initialized");

  // Display_getGFX()->begin();
  // Serial.println("CapTin: Graphics Driver Initialized");

  Display_getCanvas()->begin();
  Serial.println("CapTin: GFX Canvas Initialized");

  if ( SD_mount() == ERR_NONE )
  {
    Serial.println("CapTin: SD Card Mounted");
  }
  else
  {
    Serial.println("Error: SD Card Failed to Mount");
  }

  #if ( CFG_DEV )
  Init_Task_Dev();
  #else
  Init_Task_CapTin();
  #endif

  /* Initialize the relevant tasks */
  //Init_Task_TicTacToe();
  //Init_Task_SlotMachine();
  //Init_Task_Hacker();
  
}

void loop(void)
{
}