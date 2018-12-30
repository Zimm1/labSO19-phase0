#include "disk.h"

volatile dtpreg_t *disk = (dtpreg_t*) DEV_REG_ADDR(IL_DISK, 0);

static unsigned int tp_status(volatile dtpreg_t *tp);
static unsigned int tp_geometry(volatile dtpreg_t *tp);

int disk_read(void* address, unsigned int sectnum, unsigned int headnum) {

    unsigned int stat;

    stat = tp_status(disk);

    if (stat != ST_DEVICE_READY){
        return -1;
    }

    sectnum = sectnum << ONE_BYTE_OFFSET;
    headnum = (headnum << ONE_BYTE_OFFSET) << ONE_BYTE_OFFSET;

    disk->data0 = (unsigned int) address;
    disk->command = (headnum | sectnum | CMD_READBLK);

    while ((stat = tp_status(disk)) == ST_DEVICE_BUSY);

    disk->command = CMD_ACK;

    return stat;
}

int disk_write(void* address,unsigned int sectnum,unsigned int headnum) {
    
    unsigned int stat;

    stat = tp_status(disk);
    
    if (stat != ST_DEVICE_READY){
        return -1;
    }

    sectnum = sectnum << ONE_BYTE_OFFSET;
    headnum = (headnum << ONE_BYTE_OFFSET) << ONE_BYTE_OFFSET;

    disk->data0 = (unsigned int) address;
    disk->command = ((headnum | sectnum) | CMD_WRITEBLK);

    while ((stat = tp_status(disk)) == ST_DEVICE_BUSY);

    disk->command = CMD_ACK;

    return stat;
}

int disk_reset() {

    unsigned int stat;

    stat = tp_status(disk);

    if (stat != ST_DEVICE_READY) {
        return -1;
    }

    disk->command = CMD_RESET;

    while ((stat = tp_status(disk)) == ST_DEVICE_BUSY);

    disk->command = CMD_ACK;

    return stat;
}

int disk_seek(unsigned int cyl) {

    unsigned int stat;

    stat = tp_status(disk);

    if (stat != ST_DEVICE_READY) {
        return -1;
    }

    cyl = cyl << ONE_BYTE_OFFSET;
    disk->command = (CMD_SEEKCYL | cyl);

    while ((stat = tp_status(disk)) == ST_DEVICE_BUSY);

    disk->command = CMD_ACK;

    return stat;
}



bool disk_check_cyl(unsigned int cyl) {
    return cyl >= 0 && cyl < disk_get_maxcyl();
}

bool disk_check_head(unsigned int head) {
    return head >= 0 && head < disk_get_maxhead();
}

bool disk_check_sect(unsigned int sect) {
    return sect >= 0 && sect < disk_get_maxsect();
}

bool disk_check(unsigned int sect, unsigned int head) {
    return disk_check_sect(sect) && disk_check_head(head);
}



int disk_get_maxcyl() {

    unsigned int geometry;

    geometry = tp_geometry(disk);

    geometry = (geometry >> ONE_BYTE_OFFSET) >> ONE_BYTE_OFFSET;

    return geometry;
}

int disk_get_maxsect() {

    unsigned int geometry;

    geometry = tp_geometry(disk);

    return geometry & ONE_BYTE_MASK;
}

int disk_get_maxhead() {

    unsigned int geometry;

    geometry = tp_geometry(disk);

    geometry = (geometry >> ONE_BYTE_OFFSET) & ONE_BYTE_MASK;

    return geometry;
}



char* disk_show_error_message(unsigned int error) {

    switch(error) {

        case ST_DEVICE_NOT_INSTALLED: {
            return "\nDevice not installed!\n\n";
            break;
        }

        case ST_ILLEGAL_OPERATION: {
            return "\nIllegal opration!\n\n";
            break;
        }

        case ST_SEEK_ERROR: {
            return "\nSeek error!\n\n";
            break;
        }

        case ST_READ_ERROR: {
            return "\nRead error!\n\n";
            break;
        }

        case ST_WRITE_ERROR: {
            return "\nWrite error!\n\n";
            break;
        }

        case ST_DMA_ERROR: {
            return "\nDMA error!\n\n";
            break;
        }

        default: {
            return "\nUnknown error!\n\n";
        }
    }
}



static unsigned int tp_status(volatile dtpreg_t *tp) {
    return ((tp->status) & DISK_STATUS_MASK);
}

static unsigned int tp_geometry(volatile dtpreg_t *tp) {
    return tp->data1;
}