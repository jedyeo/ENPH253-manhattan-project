#include <Arduino.h>
#include <Servo.h>

#define MOTOR_A PA_2 
#define MOTOR_B PA_3
#define RAMP_SERVO PB9

#define RESO RESOLUTION_10B_COMPARE_FORMAT
#define PWMFREQ 1000

// Servo object
Servo rampServo;

void stopMotor() {
  pwm_start(MOTOR_A, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_B, PWMFREQ, 0, RESO);

  delay(1000);
}

void moveServo() {
  rampServo.write(30);
  delay(1000);
  rampServo.write(0);
  delay(1000);
}


void setup() {
  // put your setup code here, to run once:

  // single motor pin modes
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  // servo pin mode
  rampServo.attach(RAMP_SERVO);
  rampServo.write(0); //default
  delay(1500);
}

void loop() {
  //ut your main code here, to run repeatedly:

  // motor testing
  // pwm_start(MOTOR_A, PWMFREQ, 512, RESO);
  // pwm_start(MOTOR_B, PWMFREQ, 0, RESO);

  // delay(1000);

  // stopMotor();

  // pwm_start(MOTOR_A, PWMFREQ, 0, RESO);
  // pwm_start(MOTOR_B, PWMFREQ, 512, RESO);
  
  // delay(1000);

  // stopMotor();

  // moveServo();
  rampServo.write(90);
  delay(500);
  rampServo.write(0);
  delay(500);
}