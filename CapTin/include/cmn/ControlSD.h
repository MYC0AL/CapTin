/****************************************************
 * ControlSD.h
 * 
 * Helper functions for interfacing with SD card.
 * 
 ****************************************************/

#include <SD.h>
#include "Errors.h"

err_t SD_getFile( File* sd_file, const char *filename, int32_t *size );
err_t SD_closeFile( File* sd_file );
err_t SD_readFile( File* sd_file, uint8_t *buffer, int32_t length );