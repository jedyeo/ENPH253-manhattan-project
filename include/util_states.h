#ifndef UTIL_STATES_H_
#define UTIL_STATES_H_

#include <Arduino.h>

typedef enum {
    STATE_INIT = 0,
    STATE_SEARCH,
    STATE_APPROACH,
    STATE_SWEEP,
    STATE_DEPOSIT,
    STATE_REPOSITION,

} State_t;

volatile uint32_t state = STATE_INIT;

#endif