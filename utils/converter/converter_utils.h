#ifndef CONVERTER_UTILS_H
#define CONVERTER_UTILS_H

#define IS_DIGIT(x) ('0' <= x && x <='9')

int get_int(const char *str,unsigned int length);

void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char* itoa(int num,int length);

void int_to_array(int n, unsigned char* out, int length);
void int_to_hex_string(int n, char* hex);

#endif