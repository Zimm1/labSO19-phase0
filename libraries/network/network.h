#ifndef NETWORK_H
#define NETWORK_H

#include "umps/arch.h"
#include "umps/types.h"

#include "../../utils/bool/bool.h"

#define ST_NOT_INSTALLED	0
#define ST_READY			1
#define ST_ILLEGAL_OP		2
#define ST_BUSY				3
#define ST_ERROR_READ		5
#define ST_ERROR_WRITE		6
#define ST_ERROR_TRANSFER	7

#define CMD_RESET			0
#define CMD_ACK				1
#define CMD_CONF_READ		2
#define CMD_NET_READ		3
#define CMD_NET_WRITE		4
#define CMD_CONF_WRITE		5

#define CHAR_OFFSET         8
#define NET_STATUS_MASK     0xFF

typedef struct net_conf {
	bool named;
	bool interrupt;
	bool promisq;
	bool set_mac;
	unsigned char addr[6];
} net_conf_t;

int net_read(packet_t *packet);
int net_write(packet_t *packet, unsigned int length);

void net_conf_read(net_conf_t* conf);
void net_conf_write(net_conf_t* conf);
void net_conf_set_promisq(unsigned int mode, net_conf_t* net_conf);

void net_reset();

void net_packet_build(packet_t *packet, unsigned char *addr, char *data, int length);

#endif