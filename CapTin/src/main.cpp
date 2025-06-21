
#include "cmn/DrawJPEG.h"
#include "cmn/ControlSD.h"
#include "cmn/ControlDisplay.h"
#include "drv/TaskSetup.h"

void setup()
{

  Serial.begin(9600);

  Display_getGFX()->begin();
  Serial.println("CapTin: Graphics Library Initialized");

  if ( SD_mount() == ERR_NONE )
  {
    Serial.println("CapTin: SD Card Mounted");
  }
  else
  {
    Serial.println("Error: SD Card Failed to Mount");
  }

  /* Initialize the CapTin task */
  Init_Task_CapTin();
}

void loop(void)
{
}