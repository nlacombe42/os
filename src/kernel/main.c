#include <system.h>
#include <hal.h>
#include <scrn.h>
#include <kb.h>
#include <time.h>
#include <mem.h>

//Fault handler
void fh(int err)
{
	scrn_puts(hal_irq_fault_getMessage(err));
	scrn_putch('\n');
	
	//ullint ip=hal_getIP();
	
	char buf[7];
	htoa(buf, 0xabcdef);
	
	scrn_puts("IP: ");
	scrn_puts(buf);
	scrn_putch('\n');
	
	hal_halt();
}

void main()//multiboot_info_t* mbi, uint magic)
{
	scrn_init();

	scrn_puts("\tFlux OS\n42\n\nStarting up...\n");

	hal_init();
	hal_irq_fault_setHandler(fh);
	kb_init();
	time_init();

	scrn_puts("Finished startup :)\n");
	
	/*
	if(magic==MULTIBOOT_BOOTLOADER_MAGIC)
	{
		mem_showMm(mbi);
	}
	else
	{
		scrn_puts("Error: no multiboot support\n");
	}*/
	
	uint magic=hal_MB_getNum();
	
	scrn_puts("Multiboot magic (true): ");
	scrn_putint(MULTIBOOT_BOOTLOADER_MAGIC);
	scrn_puts("\nMultiboot magic (received): ");
	scrn_putint(magic);
	scrn_puts("\nequal: ");
	
	if(magic==MULTIBOOT_BOOTLOADER_MAGIC)
		scrn_puts("TRUE\n");
	else
		scrn_puts("FALSE\n");
	
	//hal_MB_getInfo();

	hal_halt();
}

