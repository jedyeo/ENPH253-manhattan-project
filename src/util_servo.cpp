#include <Servo.h>
#include <Arduino.h>
#include "pin_define.h"
#include "util_servo.h"

Servo rampServo;
Servo sweepServo;

void depositCan() {
    rampServo.write(20);
}

void retractRamp() {
    rampServo.write(180);
}

void extendSweeper() {
    sweepServo.write(180);
}

void sweepCan() {
    sweepServo.write(90);
}

void initServo() {
    // servo pin mode
    rampServo.attach(RAMP_SERVO);
    retractRamp();

    sweepServo.attach(SWEEP_SERVO);
}
