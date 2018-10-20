#ifndef MEM_H
#define MEM_H

#include <hal.h>

#if defined(X86)
#include <multiboot.h>
#endif

//Using simple bool array algorithm for memory allocation

//memory discovery
void mem_init();

//size in bytes
void* mem_alloc(size_t size);
void mem_free(void* p);

#if defined(X86)
#include <scrn.h>
void mem_showMm(multiboot_info_t* mbi);
#endif

#endif

