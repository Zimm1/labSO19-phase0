#include "umps/types.h"

#include "../../libraries/network/network.h"
#include "../../libraries/terminal/terminal.h"

#include "../../utils/converter/converter_utils.h"
#include "../../utils/print/print_utils.h"
#include "../../utils/system/system_utils.h"


#define LINE_BUF_SIZE 64

unsigned char DEST_ADDR[6] = {0x12, 0x12, 0x12, 0x12, 0x12, 0x12};


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
	term_puts("Packet:\n");

	term_puts("    - destination: ");
	print_mac_addr(DEST_ADDR);
	term_putchar('\n');

	term_puts("    - data:        ");
	int length = term_readline(buf, LINE_BUF_SIZE);

	net_packet_build(packet, DEST_ADDR, buf, length);
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
	char buf[LINE_BUF_SIZE];
	packet_t packet;

	net_conf_read(&net_conf);
	print_net_conf(&net_conf);
	net_conf_set_promisq(0, &net_conf);

	while(1) {
		term_puts("\nNetwork read / write (r/w, e to exit): ");
		char c = choice(buf);

		if (c == 'w') {
			write(&packet, buf);
		} else if (c == 'r') {
			term_puts("Listening for messages...\n");
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
