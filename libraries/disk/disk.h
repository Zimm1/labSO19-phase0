
#ifndef DISK_H_
#define DISK_H_

#include "umps/arch.h"
#include "umps/types.h"

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

#define BIT_OFFSET                      8
#define TERM_STATUS_MASK                0xFF
#define GEOMETRY_MASK                   0xFFFFFFFF
#define ONE_BYTE_MASK                   0xFF

int disk_read(void* i,unsigned int sectnum, unsigned int headnum);
int disk_write(void* i,unsigned int sectnum,unsigned int headnum);
int reset();
int seek(unsigned int cyl);

int get_maxhead();
int get_maxsect();
int get_maxcyl();

int check(unsigned int sect, unsigned int head);
int check_cyl(unsigned int cyl);
int check_head(unsigned int head);
int check_sect(unsigned int sect);

char* show_error_message(unsigned int error);

#endif