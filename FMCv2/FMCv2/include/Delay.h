#ifndef FMCV2_INCLUDE_DELAY_H_
#define FMCV2_INCLUDE_DELAY_H_

#include "time.h"

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

#endif /* FMCV2_INCLUDE_DELAY_H_ */
