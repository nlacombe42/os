#ifndef SCRN_H
#define SCRN_H

#include <hal.h>

#define SCRN_BLACK 0
#define SCRN_BLUE 1
#define SCRN_GREEN 2
#define SCRN_CYAN 3
#define SCRN_RED 4
#define SCRN_MAGENTA 5
#define SCRN_BROWN 6
#define SCRN_LIGHT_GREY 7
#define SCRN_DARK_GREY 8
#define SCRN_LIGHT_BLUE 9
#define SCRN_LIGHT_GREEN 10
#define SCRN_LIGHT_CYAN 11
#define SCRN_LIGHT_RED 12
#define SCRN_LIGHT_MAGENTA 13
#define SCRN_LIGHT_BROWN 14
#define SCRN_WHITE 15

void scrn_init();

void scrn_clear();
void scrn_putch(const char c);
void scrn_putint(int i);
void scrn_puts(const char *text);
void scrn_setColor(const char forecolor, const char backcolor);

#endif

