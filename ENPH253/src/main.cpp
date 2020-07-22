#include <Arduino.h>
#include <Servo.h>

// Pin Definitions
// y A9 g A10
#define MOTOR_R1 PB_8 // forward
#define MOTOR_R2 PB_9 // rev 
#define MOTOR_L1 PB_6 // forward
#define MOTOR_L2 PB_7 // rev
#define RAMP_SERVO PA2 

#define RESO RESOLUTION_10B_COMPARE_FORMAT
#define PWMFREQ 1000

Servo rampServo;

void stopMotor() {
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO);
}

void moveForward(int time) {
  pwm_start(MOTOR_R1, PWMFREQ, 1023, RESO); // go forward
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); // do not reverse
  pwm_start(MOTOR_L1, PWMFREQ, 1023, RESO); // go forward
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); // do not reverse
  delay(time);
  stopMotor();
}

void moveBackwards(int time) {
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 1023, RESO); 
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L2, PWMFREQ, 1023, RESO); 
  delay(time);
  stopMotor();
}

void turnRight(int time) {
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 1023, RESO); 
  pwm_start(MOTOR_L1, PWMFREQ, 1023, RESO); 
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); 
  delay(time);
  stopMotor();
}

void turnLeft(int time) {
  pwm_start(MOTOR_R1, PWMFREQ, 1023, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L2, PWMFREQ, 1023, RESO); 
  delay(time);
  stopMotor();
}

void depositCan() {
  rampServo.write(60);
}

void retractRamp() {
  rampServo.write(180);
}

void simpleTest() {
  moveForward(750);
  depositCan();

  delay(1000);
  retractRamp();
  delay(10000);
}

void setup() {
  // put your setup code here, to run once:

  // single motor pin modes
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);

  // start at zero duty cycle
  stopMotor();

  // servo pin mode
  rampServo.attach(RAMP_SERVO);
  retractRamp();

  // wait 5s to gather your thoughts and pray to andre
  delay(5000);
}

void loop() {
  //simpleTest();

  moveForward(500);
  delay(500);
  moveBackwards(500);
  delay(500);
  turnRight(1000);
  delay(500);
  turnLeft(1000);
  delay(500);
}
