#pragma once

#include "Servo.h"

#define BUTTON_PIN 2
#define BUZZER_PIN 7
#define SERVO_PIN 5

void setup_layout();

int read_button();
int read_button_once();
float read_acceleration_y();
float read_altitude();

void set_servo(int angle);