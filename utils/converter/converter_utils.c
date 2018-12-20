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

int get_int(const char *str,unsigned int length){

    int retval = 0;
    int valid = 0;
    int c;

    for(c = 0;c < length; c++){
        if(IS_DIGIT(*str)){
            valid++;
            retval = retval * 10 + *str -'0';
        }
        str = str + 1;
    }

    if(valid){
        return retval;
    } else {
        return -1;
    }
}

void swap(char *x, char *y){
    char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j){
    while(i<j)
        swap(&buffer[i++], &buffer[j--]);
    return buffer;
}

char* itoa(int num,int length){
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
    if(i == 0 )
        buffer[i++] = '0';

    buffer[i] = '\0';

    return reverse(buffer, 0, i-1);
}