#ifndef UTIL_MOTOR_H_
#define UTIL_MOTOR_H_

#include <Arduino.h>
#include "pin_define.h"

void stopMotor();
void moveForward(int speed, int time);
void moveBackwards(int speed, int time);
void turnRight(int speed, int time);
void turnLeft(int speed, int time);
void dance();

#endif
