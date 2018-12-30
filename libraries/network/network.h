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


/**
  * Struct of a network interface configuration
  *
  * named : 	if true, the interface sets the sender address to its address while sending a packet
  *	interrupt: 	if true, the interface generates an interrupt when a packet is received
  * promisq:	if true, the interface intercepts all packets on the network
  * set_mac:	if true, addr field will be set as the current network interface address on the next net_conf_write
  * addr:		current network interface address
  *
  **/
typedef struct net_conf {
	bool named;
	bool interrupt;
	bool promisq;
	bool set_mac;
	unsigned char addr[6];
} net_conf_t;

/**
  * Read / write packets from / to the network interface
  *
  * packet: struct that contains data to send to / received from the interface
  *	length: length of the data field of the packet to send
  *
  * returns -1 if there was an error, the message length otherwise
  *
  **/
int net_read(packet_t *packet);
int net_write(packet_t *packet, unsigned int length);

/**
  * Read / write the network interface configuration
  * 
  * conf: struct that contains the current network cofiguration
  *
  * returns -1 if there was an error, 0 otherwise
  *
  **/
int net_conf_read(net_conf_t* conf);
int net_conf_write(net_conf_t* conf);

/**
  * Sets the current interface ability to intercept all packets on the network
  * 
  * mode: if true, the interface will intercept all packets on the network
  *		  if false, only the packets sent to the interface will be received
  *
  * returns -1 if there was an error, 0 otherwise
  *
  **/
int net_conf_set_promisq(unsigned int mode);

/**
  * Empties the read and write buffers, resets the network address to default
  *
  *	returns -1 if there was an error, 0 otherwise
  *
  **/
int net_reset();

/**
  * Creates a packet from the provided parameters
  *
  * packet: struct to store the new packet in
  * addr:	destination address of the packet
  *	data:	message in the body of the packet
  *	length:	length of the message
  *
  **/
void net_packet_build(packet_t *packet, unsigned char *addr, char *data, int length);

#endif