#include "os.h"

extern void schedule(void);

#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint32_t _tick = 0;

void timer_load(int interval)
{
	int id = r_mhartid();
	*(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + interval;
}

void timer_init()
{
	timer_load(TIMER_INTERVAL);
	w_mie(r_mie() | MIE_MTIE);
}

void timer_handler() 
{
	_tick++;
    if(_tick < 10) {
        printf("\r\033[K00:00:0%d", _tick % 60);
    }
    else {
        printf("\r\033[K00:00:%d", _tick % 60);
    }
	timer_load(TIMER_INTERVAL);

	schedule();
}
