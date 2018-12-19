#include "network.h"

#include "../../utils/converter/converter_utils.h"


volatile dtpreg_t *network = (dtpreg_t*) DEV_REG_ADDR(IL_ETHERNET, 0);
unsigned int mask;

int net_read(packet_t *packet) {
    unsigned int stat;

    stat = network->status;
    if (stat != ST_READY) {
        return -1;
    }

    network->data0 = (unsigned int) packet;
    network->data1 = (unsigned) 1;
    network->command = CMD_NET_READ;

    while ((stat = network->status) == ST_BUSY);

    if (stat != ST_READY) {
        return -1;
    }

    network->command = CMD_ACK;

    return network->data1;
}

int net_write(packet_t *packet, unsigned int length) {
    unsigned int stat;

    stat = network->status;
    if (stat != ST_READY) {
        return -1;
    }

    network->data0 = (unsigned int) packet;
    network->data1 = length + 14;
    network->command = CMD_NET_WRITE;

    while ((stat = network->status) == ST_BUSY);

    if (stat == ST_ERROR_WRITE) {
        return -1;
    }

    network->command = CMD_ACK;

    return 0;
}

void net_conf_read(net_conf_t* conf) {
    unsigned int stat;

    stat = network->status;
    if (stat != ST_READY) {
        return;
    }

    network->command = CMD_CONF_READ;

    while ((stat = network->status) == ST_BUSY);

    mask = 1 << 16;
    conf->named = (network->data0 & mask) >> 16;

    mask = mask << 1;
    conf->interrupt = (network->data0 & mask) >> 17;

    mask = mask << 1;
    conf->promisq =  (network->data0 & mask) >> 18;

    mask = mask << 5;
    conf->set_mac =  (network->data0 & mask) >> 23;

    conf->addr[0] = (unsigned char) (network->data0 >> 8);
    conf->addr[1] = (unsigned char) (network->data0);
    conf->addr[2] = (unsigned char) (network->data1 >> 24);
    conf->addr[3] = (unsigned char) (network->data1 >> 16);
    conf->addr[4] = (unsigned char) (network->data1 >> 8);
    conf->addr[5] = (unsigned char) (network->data1);

    network->command = CMD_ACK;
}

void net_conf_write(net_conf_t* conf) {
    unsigned int stat;

    stat = network->status;
    if (stat != ST_READY) {
        return;
    }

    network->command = CMD_CONF_WRITE;

    while ((stat = network->status) == ST_BUSY);

    network->command = CMD_ACK;
}

void net_conf_set_promisq(unsigned int mode, net_conf_t* net_conf) {
    net_conf_read(net_conf);

    unsigned int mask = 1 << 18;

    if (mode == 1) {
        network->data0 = network->data0 | mask;
    } else {
        mask = ~mask;
        network->data0 = network->data0 & mask;
    }

    net_conf_write(net_conf);
}

void net_reset() {
    unsigned int stat;

    stat = network->status;
    if (stat != ST_READY) {
        return;
    }

    network->command = CMD_RESET;

    while ((stat = network->status) == ST_BUSY);

    network->command = CMD_ACK;
}

void net_packet_build(packet_t *packet, unsigned char *addr, char *data, int length) {
    int i;
    for (i = 0; i < 6; ++i) {
        packet->dest[i] = addr[i];
    }

    for (i = 0; i < length; ++i) {
        packet->data[i] = data[i];
    }

    int_to_array(length, packet->proto, 2);
}