#ifndef TIME_H
#define TIME_H

#include <hal.h>

//how much time passes between ticks (in miliseconds)
extern const uint time_TICKINT;

//return the number of miliseconds since bootup
size_t time();

//wait (loops) a number of miliseconds
void time_wait(size_t ms);

void time_init();

#endif

