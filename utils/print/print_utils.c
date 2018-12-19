#include "print_utils.h"

#include "../../libraries/terminal/terminal.h"

#include "../converter/converter_utils.h"


void print_bool(bool b) {
	term_puts(b ? "True" : "False");
}

void print_mac_addr(unsigned char *addr) {
	int i;
	char hex[3];

	for (i = 0; i < 6; ++i) {
		int_to_hex_string(addr[i], hex);
		term_puts(hex);
		if (i != 5) {
			term_putchar(':');
		}
	}
}

void print_net_conf(net_conf_t* conf) {
	term_puts("Network configuration:\n");

	term_puts("    - mac address: ");
	print_mac_addr(conf->addr);
	term_putchar('\n');

	term_puts("    - named:       ");
	print_bool(conf->named);
	term_putchar('\n');

	term_puts("    - interrupt:   ");
	print_bool(conf->interrupt);
	term_putchar('\n');

	term_puts("    - promisq:     ");
	print_bool(conf->promisq);
	term_putchar('\n');

	term_puts("    - set_mac:     ");
	print_bool(conf->set_mac);
	term_putchar('\n');
}