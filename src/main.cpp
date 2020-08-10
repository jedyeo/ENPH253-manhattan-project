#include <Arduino.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include "pin_define.h"
#include "util_motor.h"
#include "util_states.h"
#include "util_servo.h"

#define NUM_SEARCH 15
#define DIST_BUFFER 2
#define THRESHOLD 500

Ultrasonic ultrasonic(TRIG, ECHO);
int dists[20];


void takeMeasurement(int i) {
    int dist_cm = ultrasonic.read();
    Serial1.println(dist_cm);
    dists[i] = dist_cm;
}

bool tapeDetected() {
    Serial1.println("tape deteced:");
    Serial1.println(analogRead(TAPE_SENSOR));

    if (analogRead(TAPE_SENSOR) >= THRESHOLD) {
        return true;
    } else {
        return false;
    }
}

bool search() {
    int search_count = 0;

    for (int i = 0; i < NUM_SEARCH; i++) {
        if (tapeDetected()) { 
            return false;
        }
        takeMeasurement(i);
        turnLeft(900, 75);
        delay(10);
    }

    int minDist = 10000;

    for (int j = 0; j < NUM_SEARCH; j++) {
        if (dists[j] < minDist) {
            minDist = dists[j];
        }
    }

    while (search_count < 1500) {
        if (tapeDetected()) { 
            return false;
        }
        if (ultrasonic.read() <= minDist) {
            moveBackwards(1023, 100);
            return true;
        } else {
            turnRight(900, 100);
            delay(10);
        }
        search_count += 100;
    }

    return false;
}

bool approach() {
    int distToCan = ultrasonic.read();

    while (distToCan > 14) {
        if (tapeDetected()) { 
            return false;
        }
        moveForward(1023, 50);
        distToCan = ultrasonic.read();
    }

    moveForward(1023, 250);
    return true;
}

void sweep() {
    // extendSweeper();
    // delay(500);
    // sweepCan();
    // delay(500);
    // extendSweeper();
}

void deposit() {
    turnLeft(900,75);
    depositCan();
    delay(1000);
    retractRamp();
}

void reposition() {
    turnRight(900, 1000);
}

void entertain() {
    while (true) {
        moveForward(1023, 300);
        depositCan();
        delay(250);
        moveBackwards(1023, 300);
        retractRamp();
        delay(250);
        turnLeft(1023, 750);
        depositCan();
        delay(250);
        turnRight(1023, 750);
        retractRamp();
        delay(500);
        depositCan();
        turnRight(1023, 750);
        delay(500);
        retractRamp();
        delay(500);
    }
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
    
    // Servo init
    initServo();
    extendSweeper();

    // Tape sensor
    pinMode(TAPE_SENSOR, INPUT);

    Serial1.println("waiting for button press");

    // pin mode buttons
    pinMode(PA4, INPUT_PULLDOWN);
    pinMode(PB3, INPUT_PULLDOWN);

    while (true) {
        if (digitalRead(PA4)) {
            Serial1.println("do robot stuff");
            Serial1.println("we're done waiting!");
            state = STATE_INIT; 
            break;
        }

        if (digitalRead(PB3)) {
            Serial1.println("give em a show");
            entertain();
        }
    }

    Serial1.println("Executing loop");
}

void loop() {
#if 1
    if (state == STATE_INIT) {
        moveBackwards(850, 600);
        state = STATE_SEARCH;
    }

    if (state == STATE_SEARCH) {
        if (search()) {
            state = STATE_APPROACH;
        } else {
            state = STATE_TAPE_DETECTED;
        }
    }

    if (state == STATE_APPROACH) {
        if (approach()) {
            state = STATE_SWEEP;
        } else {
            state = STATE_TAPE_DETECTED;
        }
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
        moveBackwards(900, 750);
        reposition();
        state = STATE_SEARCH;
    }

    if (state == STATE_TAPE_DETECTED) {
        delay(500);
        moveBackwards(900,1000);
        turnLeft(1023, 350);
        state = STATE_SEARCH;
    }
#endif
 //   Serial1.println("LOOP TAPE:");
   // Serial1.println(analogRead(TAPE_SENSOR));
    // Serial1.println("Sweeping");
    // extendSweeper();
    // delay(500);
    // sweepCan();
    // delay(500);

}
