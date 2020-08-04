#include <Servo.h>
#include "pin_define.h"
#include "util_servo.h"

Servo rampServo;

void depositCan() {
    rampServo.write(20);
}

void retractRamp() {
    rampServo.write(180);
}
