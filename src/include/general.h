#ifndef GENERAL_H
#define GENERAL_H

#include <hal_def.h>

char* itoa(char* buf, int num);
size_t ilen(int num); //number of character that itoa(char*,uint) is going to write

char* htoa(char* buf, ulong num); //hex to ascii. always returns 4B (32bit) + 1B for '\0' + 2B for "0x"

size_t strlen(const char* str);

void* memset(void* data, uchar val, size_t len);
void* memcpy(void* dest, const void* src, size_t count);
ushort* memsetw(unsigned short *dest, unsigned short val, size_t count);

char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t ml);

char* strcat(char* dest, const char* str);
char* strncat(char* dest, const char* str, size_t ml);

#endif
