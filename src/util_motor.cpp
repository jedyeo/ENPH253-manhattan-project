#include "util_motor.h"

void stopMotor() {
    pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
    pwm_start(MOTOR_R2, PWMFREQ, 0, RESO);
    pwm_start(MOTOR_L1, PWMFREQ, 0, RESO);
    pwm_start(MOTOR_L2, PWMFREQ, 0, RESO);
}

void moveForward(int speed, int time) {
    pwm_start(MOTOR_R1, PWMFREQ, speed, RESO); // go forward
    pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); // do not reverse
    pwm_start(MOTOR_L1, PWMFREQ, speed, RESO); // go forward
    pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); // do not reverse
    delay(time);
    stopMotor();
}

void moveBackwards(int speed, int time) {
    pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
    pwm_start(MOTOR_R2, PWMFREQ, speed, RESO); 
    pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
    pwm_start(MOTOR_L2, PWMFREQ, speed, RESO); 
    delay(time);
    stopMotor();
}

void turnRight(int speed, int time) {
    pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
    pwm_start(MOTOR_R2, PWMFREQ, speed, RESO); 
    pwm_start(MOTOR_L1, PWMFREQ, speed, RESO); 
    pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); 
    delay(time);
    stopMotor();
}

void turnLeft(int speed, int time) {
    pwm_start(MOTOR_R1, PWMFREQ, speed, RESO);
    pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); 
    pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
    pwm_start(MOTOR_L2, PWMFREQ, speed, RESO); 
    delay(time);
    stopMotor();
}

void dance() {
    moveForward(767, 500);
    delay(500);
    moveBackwards(767, 500);
    delay(500);
    turnRight(767, 500);
    delay(500);
    turnLeft(767, 500);
    delay(500);
}
