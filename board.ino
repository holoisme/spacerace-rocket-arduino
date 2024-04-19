// #include <Servo.h>

#include "board.h"
#include "utils.h"

Servo servo;

void setup_layout() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	servo.attach(SERVO_PIN);
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

float read_acceleration_y() {
	return 0.0f;
}

float read_altitude() {
	return 0.0f;
}

void set_servo(int angle) {
	servo.write(angle);
}