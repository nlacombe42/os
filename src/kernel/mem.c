#include <mem.h>

//free block used for alloc and free
size_t mem_base_addr;
size_t mem_length;

//allocation map
//bool[] mem_amap;
size_t mem_block_size;

#if defined(X86)
typedef struct
{
	uint size; //in B
	ullint base_addr;
	ullint length;
	uint type;
} Mmm;
#endif

//memory discovery
void mem_init()
{
	//
}

//size in bytes
void* mem_alloc(size_t size);
void mem_free(void* p);

#if defined(X86)
void mem_showMm(multiboot_info_t* mbi)
{
	//check bit 6 of mbi->flags to make sure everything is ok
	
	if(mbi->flags&0x40)
	{
		Mmm* mmap=(Mmm*)mbi->mmap_addr;
	
		uint num=0;
	
		while((uint)mmap<mbi->mmap_addr+mbi->mmap_length)
		{
			if(mmap->size>=20)
			{
				num++;
				scrn_puts("PAGE ");
			
				if(mmap->type==1)
					scrn_puts("FREE\n");
				else
					scrn_puts("TAKEN\n");
				
				scrn_puts("base addr: ");
				scrn_putint(mmap->base_addr);
				scrn_puts("\nsize: ");
				scrn_putint(mmap->length);
				scrn_puts("\n");
			}
		
			mmap=(Mmm*)((uint)mmap+mmap->size+sizeof(uint));
		}
	
		scrn_puts("Num: ");
		scrn_putint(num);
		scrn_putch('\n');
	}
	else
	{
		scrn_puts("Error: multiboot memory map not available\n");
	}
}
#endif


