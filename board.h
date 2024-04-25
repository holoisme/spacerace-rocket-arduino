#pragma once

#include "Servo.h"

#define BUTTON_PIN 6
#define BUZZER_PIN 8
#define SERVO_PIN 5
#define SPI_CS_PIN 4

void setup_layout();

int read_button();
int read_button_once();
float read_temperature();
float read_pressure();
float read_altitude();
float read_sealevel_pressure();

void set_servo(int angle);