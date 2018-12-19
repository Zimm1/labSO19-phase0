#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include "../bool/bool.h"
#include "../../libraries/network/network.h"

void print_bool(bool b);
void print_mac_addr(unsigned char *addr);
void print_net_conf(net_conf_t* conf);

#endif