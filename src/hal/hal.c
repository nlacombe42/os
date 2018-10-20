#include <hal.h>

#if defined(X86)

const uint hal_irq_maxIRQ=16;
const uint hal_irq_numFaultMsg=32;

void (*hal_irq_fault_handler)(int err)=0;

void* hal_irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//faults descriptions
const char* hal_irq_fault_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

#endif

void hal_init()
{
	//init IDT
	hal_idt_init();

	//init IRQ fault handler
	hal_isrs_init();

	//init (custom) IRQ
	hal_irq_init();

	#if defined(X86)
	__asm__ __volatile__ ("sti"); //start IRQ (had been block at the start)
	#endif
}

uchar inportb (ushort _port)
{
	#if defined(X86)
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
	#endif
}

void outportb (ushort _port, const char _data)
{
	#if defined(X86)
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
	#endif
}

void hal_irq_fault_setHandler(void (*handler)(int err))
{
	hal_irq_fault_handler=handler;
}

const char* hal_irq_fault_getMessage(int err)
{
	if(err<hal_irq_numFaultMsg)
		return hal_irq_fault_messages[err];
	else
		return "";
}

void hal_irq_setHandler(int irq, void (*handler)(int i))
{
    hal_irq_routines[irq]=(void*)handler;
}

void hal_irq_unset_handler(int irq)
{
    hal_irq_routines[irq]=0;
}

uint hal_irq_max()
{
	return hal_irq_maxIRQ;
}

#if defined(X86)

//common IRQ fault handler
void fault_handler(struct regx86* r)
{
	//hal_int_info* info

	if (r->int_no<32&&hal_irq_fault_handler)
	{
		//
		hal_irq_fault_handler(r->int_no);
	}
}

//common IRQ handler
void irq_handler(struct regx86* r)
{
    void (*handler)(int i);

    handler=(void (*)(int i))hal_irq_routines[r->int_no-32];

    if(handler)
        handler(r->int_no-32);

    //send signal to slave IRQ controller
    if(r->int_no >= 40)
        outportb(0xA0, 0x20);

    //send signal to master IRQ controller
    outportb(0x20, 0x20);
}

#endif

