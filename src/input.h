#ifndef _DEFS_H
#define _DEFS_H

#ifdef _WIN32
#include <windows.h>
#define sleep(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep(ms) usleep(ms*1000)
#endif


//enable non blocking input (unix systems)
void enable_nbi();
//disable non blocking input (unix systems)
void disable_nbi();
// get the pressed key
int get_key();
#endif /* _GAME_H */
