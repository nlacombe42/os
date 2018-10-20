#ifndef HAL_DEF_H
#define HAL_DEF_H

//TARGET
#define X86

//SUPPORTS: X86

#define NULL (0)

//macros
#define MIN(a, b) (a<b?a:b)

//typedefs
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullint;

#if defined(X86)

typedef unsigned int size_t;

#endif

#endif

