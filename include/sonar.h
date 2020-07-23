#ifndef SONAR_H_
#define SONAR_H_

#include <Arduino.h>
#include "pin_define.h"

uint32_t get_distance (void);
void delay_us(uint32_t us);

#endif