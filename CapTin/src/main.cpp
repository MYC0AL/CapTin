
#include "cmn/DrawJPEG.h"
#include "cmn/ControlSD.h"
#include "cmn/ControlDisplay.h"
#include "cmn/ControlTouch.h"
#include "drv/TaskSetup.h"

void setup()
{

  Serial.begin(9600);

  Touch_getDriver()->begin();
  Serial.println("CapTin: Touch Driver Initialized");
  Display_getGFX()->begin();
  Serial.println("CapTin: Graphics Driver Initialized");

  if ( SD_mount() == ERR_NONE )
  {
    Serial.println("CapTin: SD Card Mounted");
  }
  else
  {
    Serial.println("Error: SD Card Failed to Mount");
  }

  /* Initialize the relevant tasks */
  Init_Task_CapTin();
  Init_Task_TicTacToe();
  
}

void loop(void)
{
}