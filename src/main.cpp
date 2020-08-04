#include <Arduino.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include "pin_define.h"
#include "util_motor.h"
#include "util_states.h"

#define NUM_SEARCH 10

Servo rampServo;
Ultrasonic ultrasonic(TRIG, ECHO);
int dists[20];

void depositCan() {
    rampServo.write(20);
}

void retractRamp() {
    rampServo.write(180);
}

void takeMeasurement(int i) {
    int dist_cm = ultrasonic.read();
    Serial1.println(dist_cm);
    dists[i] = dist_cm;
}

void search() {
    for (int i = 0; i < NUM_SEARCH; i++) {
        takeMeasurement(i);
        turnLeft(850, 150);
    }

    int minDist = 10000;

    for (int j = 0; j < NUM_SEARCH; j++) {
        if (dists[j] < minDist) {
            minDist = dists[j];
        }
    }

    for (int k = 0; k < 20; k++) {
        if (ultrasonic.read() <= minDist) {
            break;
        }
        turnRight(850, 100);
    }
}

void approach() {
    int distToCan = ultrasonic.read();

    // CAUTION: the shortest distance could indeed have been a wall,
    // this is where you need to especially check for tape

    while(distToCan > 15) {
        moveForward(950, 50);
        distToCan = ultrasonic.read();
    }
}

void sweep() {
    // nothing here yet
}

void deposit() {
    depositCan();
    delay(1000);
    retractRamp();
}

void reposition() {
    turnRight(900, 1000);
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

    // Tape sensor
    pinMode(PB0, INPUT);

    Serial1.println("waiting for button press");

    // pressing PA4 starts the loop
    while (true) {
        if (digitalRead(PA4)) {
            Serial1.println("we're done waiting!");
            state = STATE_INIT; 
            break;
        }
    }

    Serial1.println("Executing loop");
}

void loop() {
    /* time trial test sequence */
    // moveBackwards(850, 200);
    
    // sweepLeft();
    // delay(250);
    // collectCan();
    // delay(3000);

    if (state == STATE_INIT) {
        moveBackwards(850, 200); // pick up bin
        state = STATE_SEARCH;
    }

    if (state == STATE_SEARCH) {
        search();
        state = STATE_APPROACH;
    }

    if (state == STATE_APPROACH) {
        approach();
        state = STATE_SWEEP;
    }
    
    if (state == STATE_SWEEP) {
        sweep();
        state = STATE_DEPOSIT;
    }
    
    if (state == STATE_DEPOSIT) {
        deposit();
        state = STATE_REPOSITION;
    }

    if (state == STATE_REPOSITION) {
        reposition();
        state = STATE_SEARCH;
    }
}
