#include "converter_utils.h"

void int_to_array(int n, unsigned char* out, int length) {
	int i;

	for (i = length - 1; i >= 0; --i) {
		out[i] = n % 256;
		n /= 256;
	}
}

void int_to_hex_string(int n, char* hex) {
	int i = 2;
	int mod;

	hex[0] = 48;
	hex[1] = 48;
	hex[2] = '\0';

	while (n != 0) {
		mod = n % 16;
		hex[--i] = mod >= 10 ? mod + 55 : mod + 48;
		n /= 16;
	}
}