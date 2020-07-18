#include <Arduino.h>
#include <Servo.h>

#define MOTOR_R1 PB_8// forward
#define MOTOR_R2 PB_9 // rev (yellow)
#define MOTOR_L1 PB_6 // forward
#define MOTOR_L2 PB_7 // rev
#define RAMP_SERVO PA2 

#define RESO RESOLUTION_10B_COMPARE_FORMAT
#define PWMFREQ 1000

// Servo object
Servo rampServo;

void stopMotor() {
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO);
}

void testMotor() {
  // move forward
  pwm_start(MOTOR_R1, PWMFREQ, 1023, RESO); // go forward
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); // do not reverse
  pwm_start(MOTOR_L1, PWMFREQ, 1023, RESO); // go forward
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); // do not reverse

  // move forward for 2 second
  delay(2000);

  // stationary for 2 second
  stopMotor();
  delay(2000);

  // move backwards
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 1023, RESO); 
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L2, PWMFREQ, 1023, RESO); 
  
  // move backwards for 2s
  delay(2000);

  // chill for 5s
  stopMotor();
  delay(5000);

  // turn right
  pwm_start(MOTOR_R1, PWMFREQ, 1023, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); 

  // turn right for 1s
  delay(1000);

  // chill for 2s
  stopMotor();
  delay(2000);

  // turn left
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); 
  pwm_start(MOTOR_L1, PWMFREQ, 1023, RESO); 
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); 

  // turn left for 1s
  delay(1000);

  // chill for 2s
  stopMotor();
  delay(2000);
}

void testServo() {
  rampServo.write(90);
  delay(2000);
  rampServo.write(10);
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:

  // single motor pin modes
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);

  // start at zero duty cycle
  pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_R2, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_L1, PWMFREQ, 0, RESO);
  pwm_start(MOTOR_L2, PWMFREQ, 0, RESO);

  // servo pin mode
  rampServo.attach(RAMP_SERVO);
  rampServo.write(0); //default

  // wait 5s to gather your thoughts and pray to andre
  delay(5000);
}

void loop() {
  // Put your main code here, to run repeatedly:
  testMotor();
}
