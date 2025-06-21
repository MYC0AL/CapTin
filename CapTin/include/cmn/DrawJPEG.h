/****************************************************
 * DrawJPEG.h
 * 
 * Functions to read a file from the SD card
 * and display them to the screen.
 * 
 ****************************************************/

#ifndef _JPEGFUNC_H_
#define _JPEGFUNC_H_

/**********************
 * Includes
**********************/
#include <JPEGDEC.h>
#include <SD.h>
#include "cmn/Errors.h"

/**********************
 * Variables
 **********************/

/**********************
 * Functions
 **********************/
err_t DrawJPEG( const char *filename, JPEG_DRAW_CALLBACK *jpegDrawCallback, 
               bool useBigEndian, int x, int y, int widthLimit, int heightLimit );

#endif // _JPEGFUNC_H_
