#include "converter_utils.h"
#include "../bool/bool.h"

void str_swap(char *x, char *y){
    char t = *x; *x = *y; *y = t;
}

char* str_reverse(char *buffer, int i, int j){
    while(i<j)
        str_swap(&buffer[i++], &buffer[j--]);
    return buffer;
}

int str_to_int(char *str, unsigned int length, int base){
    int retval = 0;
    int value;
    int c;

    for(c = 0; c < length; ++c){
        if (!IS_DIGIT(*str)) {
            return -1;
        }

        value = *str -'0';
        if (value > 16) {
            value -= 7;
        }
        if (value >= 42) {
            value -= 32;
        }

        retval = retval * base + value;
        str++;
    }
    return retval;
}

void str_mac_to_array(char *str, unsigned char mac[6]) {
    int i;
    for (i = 0; i < 6; ++i) {
        mac[i] = str_to_int(str, 2, 16);
        str += 3;
    }
}

char* int_to_str(int num,int length){
    int i = 0;
    char buffer[length];
    int n = num;

    while(n){
        int r = n % 10;
        if(r >= 10){
            buffer[i++] = 65 + (r - 10);
        } else {
            buffer[i++] = 48 + r;
        }
        n = n / 10;
    }
    if(i == 0 ){
        buffer[i++] = '0';
    }

    buffer[i] = '\0';

    return str_reverse(buffer, 0, i-1);
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

void int_to_array(int n, unsigned char* out, int length) {
	int i;

	for (i = length - 1; i >= 0; --i) {
		out[i] = n % 256;
		n /= 256;
	}
}