#include "board.h"

Servo servo;

void setup_layout() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	servo.attach(SERVO_PIN);
}

Servo get_servo() {
	return servo;
}
