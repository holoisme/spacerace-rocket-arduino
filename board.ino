// #include <Servo.h>

#include "board.h"
#include "utils.h"
#include "config.h"

#include <Wire.h>
#include <Adafruit_BMP085.h>

Servo servo;
Adafruit_BMP085 bmp;

void setup_layout() {
	Serial.println("Setting button...");
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	Serial.println("Attaching servo...");
	servo.attach(SERVO_PIN);
	Serial.println("Initializing BMP180...");
	if (!bmp.begin()) {
		Serial.println("Could not find the BMP180 sensor.");
		while (1) {}
	}
}

int previous_button_state;

int read_button() {
	if(digitalRead(BUTTON_PIN) == LOW)
		return TRUE;
	return FALSE;
}

int read_button_once() {
	int previous_cache = previous_button_state;
	int button_state = read_button();
	previous_button_state = button_state;
	if(previous_cache == FALSE && button_state == TRUE)
		return TRUE;
	return FALSE;
}

float read_altitude() {
	return bmp.readAltitude(SEA_LEVEL_PRESSURE_hPa * 100);
}

float read_temperature() {
	return bmp.readTemperature();
}

float read_pressure() {
	return bmp.readPressure();
}

float read_sealevel_pressure() {
	return bmp.readSealevelPressure();
}

void set_servo(int angle) {
	Serial.print("Setting the Servo angle at ");
	Serial.println(angle);
	servo.write(angle);
}