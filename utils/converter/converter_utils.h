#ifndef CONVERTER_UTILS_H
#define CONVERTER_UTILS_H


#define IS_DIGIT(x) (('0' <= x && x <='9') || ('A' <= x && x <='F') || ('a' <= x && x <='f'))


/**
  * Swaps 2 string pointers
  * x: first string
  * y: second string 
  *
  **/
void str_swap(char *x, char *y);
/**
  * Reverses a string
  *	str: string to reverse
  *	i:   first index
  *	j:	 last index
  *
  **/
void str_reverse(char *str, int i, int j);
/**
  * Converts a string to a intger, with different bases
  *	str:    string to convert
  *	length: length of str
  *	base:	base of the conversion (2, 8, 10, 16, ...)
  *
  * outputs the converted integer
  *
  **/
int str_to_int(char *str, unsigned int length, int base);
/**
  * Converts a string mac address (01:23:45:67:89:AB) to its value
  *	str: string mac address to convert
  *	mac: output value
  *
  **/
void str_mac_to_array(char *str, unsigned char mac[6]);

/**
  * Converts a integer to the corresponding string in decimal base
  *	num: input integer 
  * str: output value
  *
  **/
void int_to_str(int num, char *str);
/**
  * Converts a integer to the corresponding string in hex base
  *	num: input integer 
  * hex: output value
  *
  **/
void int_to_hex_string(int n, char* hex);
/**
  * Converts a integer to the corresponding byte array
  *	num:    input integer 
  * out:    output byte array
  * length: number of figures
  *
  **/
void int_to_array(int n, unsigned char* out, int length);

#endif