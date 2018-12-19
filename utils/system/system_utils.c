#include "system_utils.h"

#include "umps/libumps.h"
#include "umps/arch.h"

void halt(void) {
    WAIT();
    *((volatile unsigned int *) MCTL_POWER) = 0x0FF;
    while (1) ;
}