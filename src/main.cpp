#include <Arduino.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <pin_define.h>

// Pin Definitions
// y A9 g A10
#define MOTOR_R1 PB_8 // forward
#define MOTOR_R2 PB_9 // rev 
#define MOTOR_L1 PB_6 // forward
#define MOTOR_L2 PB_7 // rev

#define RESO RESOLUTION_10B_COMPARE_FORMAT
#define PWMFREQ 1000

Servo rampServo;
Ultrasonic ultrasonic(TRIG, ECHO);
int dists[20];

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

void depositCan() {
    rampServo.write(20);
}

void retractRamp() {
    rampServo.write(180);
}

void simpleTest() {
    moveForward(767, 750);
    depositCan();

    delay(1000);
    retractRamp();
    delay(10000);
}

void takeMeasurement(int i) {
    int dist_cm = ultrasonic.distanceRead();
    Serial1.println(dist_cm);
    dists[i] = dist_cm;
}

void sweepLeft() {
    for (int i = 0; i < 5; i++) {
        takeMeasurement(i);
        turnLeft(850, 150);
        delay(250);
    // i++
    }
    int myMin = 10000;
    int myMinIndex = -1;

    for (int j = 0; j < 5; j++) {
        if (dists[j] < myMin) {
            myMin = dists[j];
            myMinIndex = j;
        }
    }
    delay(1000);

   // turnRight(900, (5-myMinIndex+1) * 150);
    for (int j = 5-myMinIndex; j > 0; j--) {
        delay(250);
        turnRight(825, 150);
    }
}

void collectCan() { 
    moveBackwards(1023, 250);
    delay(250);
    int distToCan = ultrasonic.distanceRead();
    while (distToCan > 30) {
        moveForward(1023, 100);
        distToCan = ultrasonic.distanceRead();
    }

    moveForward(1023, 500);
    depositCan();
    delay(1000);
    retractRamp();
}

void setup() {
    // begin serial comms for debugging
    Serial1.begin(9600);
    Serial1.println("setup");

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

    // wait 10s to gather your thoughts and pray to andre
    delay(10000);
}

void loop() {
    Serial1.println("beginning of loop");
    moveBackwards(850, 200);
    // delay(500);
    
    sweepLeft();
    delay(250);
    collectCan();
    delay(3000);

    // moveForward(950, 800);
    // delay(250);
    // turnRight(950, 750);
    // delay(250);
    // collectCan();
    // delay(250);
    // turnRight(950, 750);
    // delay(250);
}
