#ifndef HAL_H
#define HAL_H

#include <hal_def.h>
#include <general.h>

#if defined(X86)
#include <multiboot.h>
#endif

/* List of kernel modules
 * ----------------------
 * 
 *   NAME         PREFIX       DESCRIPTION
 *   ----         ------       -----------    
 *   idt          idt          Interrupt Descriptor Table
 *   irq          irq          Interrupt Request Handler (custom IRQ)
 */

//set IRQ handler
//num is the IRQ #
//handler is a function pointer of type void f(int i); (parameter i is the interrupt number
void hal_irq_setHandler(int num, void (*handler)(int i));

//unset IRQ handler
//num is IRQ #
void hal_irq_unsetHandler(int num);

//gets the maximum number of IRQ
uint hal_irq_max();

//sets the fault hander
void hal_irq_fault_setHandler(void (*handler)(int err));

//return the CPU exception message according to the error code
const char* hal_irq_fault_getMessage(int err);

extern void hal_halt(); //halt (hlt in a loop) (in start*.asm)
extern ullint hal_getIP(); //get instruction pointer (in start*.asm)

void hal_init();

uchar inportb(ushort _port);
void outportb(ushort _port, const char _data);

struct
{
	uint int_no;
	uint err_code;
	ullint ip;
} hal_int_info;

#if defined(X86)

//defiend in startx86.asm
extern uint hal_MB_getNum();
extern multiboot_info_t* hal_MB_getInfo();

struct regx86
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
} Regx86;

extern void hal_idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, const char flags);
extern void hal_idt_init();
extern void hal_irq_init();
extern void hal_isrs_init();

#endif

#endif

