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

int disk_read(void* address, unsigned int sectnum, unsigned int headnum);
int disk_write(void* address, unsigned int sectnum, unsigned int headnum);
int disk_reset();
int disk_seek(unsigned int cyl);

int disk_get_maxhead();
int disk_get_maxsect();
int disk_get_maxcyl();

bool disk_check(unsigned int sect, unsigned int head);
bool disk_check_cyl(unsigned int cyl);
bool disk_check_head(unsigned int head);
bool disk_check_sect(unsigned int sect);

char* disk_show_error_message(unsigned int error);

#endif