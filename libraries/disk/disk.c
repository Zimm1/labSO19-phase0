#include "disk.h"

/*Reference to the first disk device*/
volatile dtpreg_t *disk = (dtpreg_t*) DEV_REG_ADDR(IL_DISK, 0);

/*Returns the status of the disk*/
static unsigned int tp_status(volatile dtpreg_t *tp);
/*Returns the physical characteristics of the disk's geometry stored in DATA1*/
static unsigned int tp_geometry(volatile dtpreg_t *tp);

int disk_read(void* address, unsigned int sectnum, unsigned int headnum) {

    unsigned int stat;

    stat = tp_status(disk);

    if (stat != ST_DEVICE_READY){
        return -1;
    }

    /*The sector number of the disk is stored in the second byte*/
    sectnum = sectnum << ONE_BYTE_OFFSET;
    /*The head number of the disk is stored in the third byte*/
    headnum = (headnum << ONE_BYTE_OFFSET) << ONE_BYTE_OFFSET;

    /*DATA0 is used to specify the starting physical address for write DMA operation*/
    disk->data0 = (unsigned int) address;
    disk->command = (headnum | sectnum | CMD_READBLK);

    /*Wait the end of the read on disk*/
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

    /*The sector number of the disk is stored in the second byte*/
    sectnum = sectnum << ONE_BYTE_OFFSET;
    /*The head number of the disk is stored in the third byte*/
    headnum = (headnum << ONE_BYTE_OFFSET) << ONE_BYTE_OFFSET;

    /*DATA0 is used to specify the starting physical address for read DMA operation.*/
    disk->data0 = (unsigned int) address;
    disk->command = (headnum | sectnum | CMD_WRITEBLK);

    /*Wait the end of the write on disk*/
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

    /*The number of cylinder to seek is stored in the second byte*/
    cyl = cyl << ONE_BYTE_OFFSET;
    disk->command = (CMD_SEEKCYL | cyl);

    /*Wait the end of the seek operation*/
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

    unsigned int maxcyl;

    maxcyl = tp_geometry(disk);

    /*The number of cylinders are stored in the third and fourth byte*/
    maxcyl = (maxcyl >> ONE_BYTE_OFFSET) >> ONE_BYTE_OFFSET;

    return maxcyl;
}

int disk_get_maxsect() {

    unsigned int maxsect;

    maxsect = tp_geometry(disk);

    /*The number of sectors are stored in the first byte*/
    return maxsect & ONE_BYTE_MASK;
}

int disk_get_maxhead() {

    unsigned int maxhead;

    maxhead = tp_geometry(disk);

    /*The number of heads are stored in the second byte*/
    maxhead = (maxhead >> ONE_BYTE_OFFSET) & ONE_BYTE_MASK;

    return maxhead;
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