#include "umps/types.h"

#include "../../libraries/network/network.h"
#include "../../libraries/terminal/terminal.h"

#include "../../utils/converter/converter_utils.h"
#include "../../utils/print/print_utils.h"
#include "../../utils/system/system_utils.h"


#define LINE_BUF_SIZE 64


int read(packet_t *packet) {
	int length = net_read(packet);

	if (length > 0) {
		term_puts("Packet received from ");
		print_mac_addr(packet->src);
		term_puts(" :\n");
		term_puts("    ");
		term_puts((char *)packet->data);
		term_putchar('\n');
	}

	return length == -1 ? -1 : 0;
}

int write(packet_t *packet, char *buf) {
	unsigned char dest_addr[6];
	net_conf_t net_conf;

	net_conf_read(&net_conf);

	term_puts("Packet:\n");
	term_puts("    - from: ");
	print_mac_addr(net_conf.addr);
	term_putchar('\n');

	term_puts("    - to:   ");
	term_readline(buf, LINE_BUF_SIZE);
	str_mac_to_array(buf, dest_addr);

	term_puts("    - data: ");
	int length = term_readline(buf, LINE_BUF_SIZE);

	net_packet_build(packet, dest_addr, buf, length);
	return net_write(packet, length);
}

char choice(char *buf) {
	char operation = 'a';

	while (operation != 'r' && operation != 'w' && operation != 'e') {
		term_readline(buf, LINE_BUF_SIZE);
		operation = buf[0];
	}

	return operation;
}

int main(int argc, char *argv[]) {
	net_conf_t net_conf;
	packet_t packet;
	char buf[LINE_BUF_SIZE];

	net_conf_read(&net_conf);
	print_net_conf(&net_conf);

	/* The default mode is promisq ON, sets to OFF */
	net_conf_set_promisq(0);

	while(1) {
		term_puts("\nNetwork read / write (r/w, e to exit): ");
		char c = choice(buf);

		if (c == 'w') {
			write(&packet, buf);
		} else if (c == 'r') {
			term_puts("Listening for messages...\n");
			/* Keeps reading incoming messages */
			while (1) {
				read(&packet);
			}
		} else {
			break;
		}
	}

    halt();

    return 0;
}
