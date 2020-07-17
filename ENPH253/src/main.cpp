#include <Arduino.h>

#define MOTOR_A PA_2 
#define MOTOR_B PA_3
#define RESO RESOLUTION_10B_COMPARE_FORMAT
#define PWMFREQ 1000

void stopMotor() {
  pwm_start(MOTOR_A, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_B, PWMFREQ, 0, RESO);

  delay(1000);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:

  pwm_start(MOTOR_A, PWMFREQ, 512, RESO);
  pwm_start(MOTOR_B, PWMFREQ, 0, RESO);

  delay(1000);

  stopMotor();

  pwm_start(MOTOR_A, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_B, PWMFREQ, 512, RESO);
  
  delay(1000);

  stopMotor();
}