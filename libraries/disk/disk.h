#ifndef DISK_H
#define DISK_H

#include "umps/arch.h"
#include "umps/types.h"
#include "../../utils/bool/bool.h"

#define ST_DEVICE_NOT_INSTALLED         0
#define ST_DEVICE_READY                 1
#define ST_ILLEGAL_OPERATION            2
#define ST_DEVICE_BUSY                  3
#define ST_SEEK_ERROR                   4
#define ST_READ_ERROR                   5
#define ST_WRITE_ERROR                  6
#define ST_DMA_ERROR                    7

#define CMD_RESET                       0
#define CMD_ACK                         1
#define CMD_SEEKCYL                     2
#define CMD_READBLK                     3
#define CMD_WRITEBLK                    4

#define ONE_BYTE_OFFSET                 8
#define DISK_STATUS_MASK                0xFF
#define ONE_BYTE_MASK                   0xFF

/**
  * disk_read -> Read the data from disk and copy it in the memory
  * disk_write -> Write the data read from the memory in the disk
  *
  * address: the starting address of memory where the data will be read / write
  *
  * sectnum, headnum: the coordinates that indicates where the data will be read / write in the disk
  *
  * returns ST_DEVICE_READY if the operation ends without error, otherwise the error code
  *
  **/
int disk_read(void* address, unsigned int sectnum, unsigned int headnum);
int disk_write(void* address, unsigned int sectnum, unsigned int headnum);

/**
  * Reset the device and move the boom to 0.
  *
  *	returns ST_DEVICE_READY if the operation ends without error, otherwise the error code
  *
  **/
int disk_reset();

/**
  * Move the boom to the desired position
  *
  * cyl: the number of cylinder where to move the boom
  *
  *	returns ST_DEVICE_READY if the operation ends without error, otherwise the error code
  *
  **/
int disk_seek(unsigned int cyl);

int disk_get_maxhead();
int disk_get_maxsect();
int disk_get_maxcyl();

/** 
  * Check if the given coordinates (cylinder, sector, head) have a valid value
  *
  * returns true only if the coordinates are in a valid range
  *
*/
bool disk_check(unsigned int sect, unsigned int head);
bool disk_check_cyl(unsigned int cyl);
bool disk_check_head(unsigned int head);
bool disk_check_sect(unsigned int sect);

/** 
  * Translates a code error in a text error
  *
  * returns the text error
  *
*/
char* disk_show_error_message(unsigned int error);

#endif