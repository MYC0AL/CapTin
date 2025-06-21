/****************************************************
 * Errors.h
 * 
 * Common Error Codes
 * 
 ****************************************************/
#ifndef _ERRORS_H
#define _ERRORS_H

typedef short err_t;
enum
{
    ERR_NONE = 0,
    ERR_FILE_NOT_FOUND = 1,
    ERR_INVLD_PARAM = 2,
    ERR_SD_MOUNT_FAIL = 3,
};

#endif