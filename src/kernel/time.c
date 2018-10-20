#include <time.h>

const uint time_TICKINT=(1/18.222)*1000;

//time in miliseconds since bootup
size_t time_tms=0;

size_t time()
{
	return time_tms;
}

#include <scrn.h>

void time_wait(size_t ms)
{
	size_t stop=time_tms+ms;

	while(time_tms<stop)
	{
		/*scrn_puts("wait: ");
		scrn_putint(time_tms);
		scrn_puts(" < ");
		scrn_putint(stop);
		scrn_putch('\n');*/
	}
}

void time_handler(int i)
{
	time_tms+=time_TICKINT;
}

void time_init()
{
	hal_irq_setHandler(0, time_handler);
}

