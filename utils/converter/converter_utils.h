#ifndef CONVERTER_UTILS_H
#define CONVERTER_UTILS_H

#define IS_DIGIT(x) (('0' <= x && x <='9') || ('A' <= x && x <='F') || ('a' <= x && x <='f'))

void str_swap(char *x, char *y);
char* str_reverse(char *buffer, int i, int j);
int str_to_int(char *str, unsigned int length, int base);
void str_mac_to_array(char *str, unsigned char mac[6]);

char* int_to_str(int num, int length);
void int_to_hex_string(int n, char* hex);
void int_to_array(int n, unsigned char* out, int length);

#endif