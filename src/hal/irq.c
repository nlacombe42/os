#include <hal.h>

#if defined(X86)

//general purpused IRQ implemented in startx86.asm
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

//remaps IRQ 0-7 to the right IDT entry
void hal_irq_remap(void)
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void hal_irq_init()
{
    hal_irq_remap();

    hal_idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    hal_idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    hal_idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    hal_idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    hal_idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    hal_idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    hal_idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    hal_idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);

    hal_idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    hal_idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    hal_idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    hal_idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    hal_idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    hal_idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    hal_idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
    hal_idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

#endif

