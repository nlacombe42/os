#include <scrn.h>

#if defined(X86)

ushort* scrn_curTextMemPtr=(ushort*)0xB8000;
int scrn_attrib=0x02; //green on black
int scrn_cur_x=0;
int scrn_cur_y=0;

void scrn_init()
{
	//scrn_setColor(SCRN_GREEN, SCRN_BLACK);
	scrn_clear();
}

void scrn_scroll()
{
	unsigned blank, temp;

	blank=0x20|(scrn_attrib<<8);

	//row 25 is the last row
    	if(scrn_cur_y>=25)
	{
		//move up the line
	        temp=scrn_cur_y-25+1;
        	memcpy(scrn_curTextMemPtr, scrn_curTextMemPtr+temp*80, (25-temp)*80*2);

		//clear last line
	        memsetw(scrn_curTextMemPtr+(25-temp)*80, blank, 80);
	        scrn_cur_y=25-1;
	}
}

void scrn_move_cur()
{
	unsigned temp;

	temp = scrn_cur_y * 80 + scrn_cur_x;

	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

void scrn_clear()
{
	unsigned blank;
	int i;

	blank = 0x20 | (scrn_attrib << 8);

    	for(i = 0; i < 25; i++)
        	memsetw(scrn_curTextMemPtr + i * 80, blank, 80);

    	scrn_cur_x = 0;
    	scrn_cur_y = 0;
    	scrn_move_cur();
}

void scrn_putch(const char c)
{
	ushort* where;
	unsigned att = scrn_attrib << 8;

    	if(c == 0x08)
    	{
		//backspace
        	if(scrn_cur_x != 0) scrn_cur_x--;
    	}
    	else if(c == 0x09)
    	{
		//tab
        	scrn_cur_x = (scrn_cur_x + 8) & ~(8 - 1);
    	}
    	else if(c == '\r')
    	{
		//cariage return (without new line)
        	scrn_cur_x = 0;
    	}
    	else if(c == '\n')
    	{
		//enter

        	scrn_cur_x = 0;
        	scrn_cur_y++;
    	}
    	else if(c >= ' ')
    	{
        	where = scrn_curTextMemPtr + (scrn_cur_y * 80 + scrn_cur_x);
        	*where = c | att;
        	scrn_cur_x++;
    	}

    	if(scrn_cur_x >= 80)
    	{
        	scrn_cur_x = 0;
        	scrn_cur_y++;
    	}

    	scrn_scroll();
    	scrn_move_cur();
}

void scrn_putint(int i)
{
	char str[ilen(i)];
	itoa(str, i);
	
	scrn_puts(str);
}

void scrn_puts(const char *text)
{
	int i;

    	for (i = 0; i < strlen(text); i++)
    	{
        	scrn_putch(text[i]);
    	}
}

void scrn_setColor(const char forecolor, const char backcolor)
{
	//high 4bit is background low 4bit is foreground
    	scrn_attrib = (backcolor << 4) | (forecolor & 0x0F);
}

#endif


