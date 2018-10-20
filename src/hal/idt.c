#include <hal.h>

//Interrupt Descriptor Table

#if defined(X86)

struct hal_idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct hal_idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct hal_idt_entry hal_idt[256];
struct hal_idt_ptr idtp;

//implemented in startx86.asm
void idt_load();

//add interrupt handler to the table
//num is the interrupt number
//base is a pointer to the function wich handles the interrupt
void hal_idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, const char flags)
{
    hal_idt[num].base_lo = (base & 0xFFFF);
    hal_idt[num].base_hi = (base >> 16) & 0xFFFF;

    hal_idt[num].sel = sel;
    hal_idt[num].always0 = 0;
    hal_idt[num].flags = flags;
}

//install IDT
void hal_idt_init()
{
    //IDT pointer init
    idtp.limit = (sizeof (struct hal_idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&hal_idt;

    //clears IDT
    memset(&hal_idt, 0, sizeof(struct hal_idt_entry) * 256);

    /* points the processor's internal register to the new IDT */
    idt_load();
}

#endif

