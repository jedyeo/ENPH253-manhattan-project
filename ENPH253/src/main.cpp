#pragma once

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "pin_define.h"
#include "sonar.h"

// Pin Definitions
// y A9 g A10
#define MOTOR_R1 PB_8 // forward
#define MOTOR_R2 PB_9 // rev 
// #define MOTOR_L1 PB_6 // forward
// #define MOTOR_L2 PB_7 // rev

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define RESO RESOLUTION_10B_COMPARE_FORMAT
#define PWMFREQ 1000

Servo rampServo;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
u_int32_t alpha = 10;

// void stopMotor() {
//     pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
//     pwm_start(MOTOR_R2, PWMFREQ, 0, RESO);
//     pwm_start(MOTOR_L1, PWMFREQ, 0, RESO);
//     pwm_start(MOTOR_L2, PWMFREQ, 0, RESO);
// }

// void moveForward(int time) {
//     pwm_start(MOTOR_R1, PWMFREQ, 1023, RESO); // go forward
//     pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); // do not reverse
//     pwm_start(MOTOR_L1, PWMFREQ, 1023, RESO); // go forward
//     pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); // do not reverse
//     delay(time);
//     stopMotor();
// }

// void moveBackwards(int time) {
//     pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
//     pwm_start(MOTOR_R2, PWMFREQ, 1023, RESO); 
//     pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
//     pwm_start(MOTOR_L2, PWMFREQ, 1023, RESO); 
//     delay(time);
//     stopMotor();
// }

// void turnRight(int time) {
//     pwm_start(MOTOR_R1, PWMFREQ, 0, RESO);
//     pwm_start(MOTOR_R2, PWMFREQ, 1023, RESO); 
//     pwm_start(MOTOR_L1, PWMFREQ, 1023, RESO); 
//     pwm_start(MOTOR_L2, PWMFREQ, 0, RESO); 
//     delay(time);
//     stopMotor();
// }

// void turnLeft(int time) {
//     pwm_start(MOTOR_R1, PWMFREQ, 1023, RESO);
//     pwm_start(MOTOR_R2, PWMFREQ, 0, RESO); 
//     pwm_start(MOTOR_L1, PWMFREQ, 0, RESO); 
//     pwm_start(MOTOR_L2, PWMFREQ, 1023, RESO); 
//     delay(time);
//     stopMotor();
//}

// void simpleTest() {
//     moveForward(750);
//     depositCan();

//     delay(1000);
//     retractRamp();
//     delay(10000);
// }

// void dance() {
//     moveForward(500);
//     delay(500);
//     moveBackwards(500);
//     delay(500);
//     turnRight(500);
//     delay(500);
//     turnLeft(500);
//     delay(500);
// }

void depositCan() {
    rampServo.write(60);
}

void retractRamp() {
    rampServo.write(180);
}

void setup() {
    // // single motor pin modes
    // pinMode(MOTOR_R1, OUTPUT);
    // pinMode(MOTOR_R2, OUTPUT);
    // pinMode(MOTOR_L1, OUTPUT);
    // pinMode(MOTOR_L2, OUTPUT);

    // start at zero duty cycle
   // stopMotor();

    // servo pin mode
    rampServo.attach(RAMP_SERVO);
    retractRamp();

    // builtin LED for debug
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // OLED screen for debug
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();

    // wait 5s to gather your thoughts and pray to andre
    delay(5000);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.clearDisplay();
    display.println("Hello world");
    display.display();
    delay(2000);
}

void loop() {
    //simpleTest();
    //dance();
    u_int32_t dist = get_distance();
    // if (get_distance() < alpha) {
    //     digitalWrite(LED_BUILTIN, HIGH);
    // } else {
    //     digitalWrite(LED_BUILTIN, LOW);
    // }
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(dist);
    display.display();
    delay(250);
}
