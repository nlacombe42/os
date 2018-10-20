#include <general.h>

static char htoa_tbl[] = { '0', '1', '2','3','4','5','6','7','8','9','A','B','C','D','E','F' };


void* memcpy(void* dest, const void* src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

ushort* memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

char* htoa(char* buf, ulong num)
{
	buf[0]='0';
	buf[1]='x';
	buf[2]=htoa_tbl[(num&0xf000)>>16];
	buf[3]=htoa_tbl[(num&0x0f00)>>8];
	buf[4]=htoa_tbl[(num&0x00f0)>>4];
	buf[5]=htoa_tbl[ num&0x000f];
	buf[6]='\0';
	
	return buf;
}

char* itoa(char* buf, int num)
{
	int t;
	
	if(num<0)
	{
		num=-num;
		*buf++='-';
	}
	
	t=num;
	
	do ++buf; while(t/=10);
	
	*buf='\0';
	
	do *--buf='0'+num%10; while(num/=10);
	
	return buf;
}

size_t ilen(int num)
{
	size_t s=0;

	do s++; while(num/=10);
	
	if(num<0)
		s++;
	
	return s;
}

size_t strlen(const char* str)
{
	if(str==NULL)
		return 0;

	size_t i=0;
	
	while(str[i]!='\0')
		i++;
		
	return i;
}

void* memset(void* data, uchar val, size_t len)
{
	uchar* d=(uchar*)data;
	size_t i;
	
	for(i=0; i<len; i++)
		d[i]=val;
		
	return data;
}

char* strcpy(char* dest, const char* src)
{
	size_t max=strlen(src);
	size_t i;
	
	for(i=0; i<max; i++)
		dest[i]=src[i];
		
	return dest;
}

char* strncpy(char* dest, const char* src, size_t ml)
{
	size_t max=MIN(strlen(src), ml);
	size_t i;
	
	for(i=0; i<max; i++)
		dest[i]=src[i];
		
	return dest;
}

char* strcat(char* dest, const char* str)
{
	size_t dl=strlen(dest);
	size_t sl=strlen(str);
	
	if(sl==0)
		return dest;
	
	size_t i;
	
	for(i=0; i<sl; i++)
		dest[dl+i]=str[i];
		
	return dest;
}

char* strncat(char* dest, const char* str, size_t ml)
{
	size_t dl=strlen(dest);
	size_t max=MIN(strlen(str), ml);
	
	if(max==0)
		return dest;
	
	size_t i;
	
	for(i=0; i<max; i++)
		dest[dl+i]=str[i];
		
	return dest;
}

