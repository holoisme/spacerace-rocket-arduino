
#include "I2C.h"
#include "state.h"
#include "board.h"
#include "utils.h"
#include "config.h"

float acceleration_samples[ACCELERATION_N_SAMPLES];
float altitude_samples[ALTITUDE_N_SAMPLES];

void setup() {
	Serial.begin(9600);
	setup_layout();
	change_state(POWER_OFF);
}

void loop() {
	update_sensor_samples();
	switch(get_current_state()) {
		case POWER_OFF: state_power_off(); break;
		case IDLE: state_idle(); break;
		case ASCENDING: state_ascending(); break;
		case DESCENDING_PRE_MAIN: state_descending_pre_main(); break;
		case DESCENDING_POST_MAIN: state_descending_post_main(); break;
		case GROUNDED: state_grounded(); break;
	}
	delay(1);
}

void update_sensor_samples() {
	populate_array(ACCELERATION_N_SAMPLES, acceleration_samples, read_acceleration_y);
	populate_array(ALTITUDE_N_SAMPLES, altitude_samples, read_altitude);
}

void state_power_off() {
	noTone(BUZZER_PIN);
	digitalWrite(LED_BUILTIN, LOW);
	set_servo(0);

	int button_state = read_button_once();
	if(button_state == TRUE)
		change_state(IDLE);
}

void state_idle() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(90);
	tick_no_delay(IDLE_TICK_INTERVAL, IDLE_TICK_FREQUENCY);

	int button_state = read_button_once();
	if(button_state == TRUE)
		change_state(POWER_OFF);

	float current_acceleration = average_array(ACCELERATION_N_SAMPLES, acceleration_samples);
	float current_altitude = average_array(ALTITUDE_N_SAMPLES, altitude_samples);

	if(current_acceleration >= IDLE_ACCELERATION_THRESHOLD && current_altitude >= IDLE_ALTITUDE_THRESHOLD)
		change_state(ASCENDING);
}

void state_ascending() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEFAULT_SERVO_POSITION);
	tick_continuously_no_delay(4000, 250, 350);

	int button_state = read_button_once();
	if(button_state == TRUE)
		change_state(DESCENDING_PRE_MAIN);

	float current_acceleration = average_array(ACCELERATION_N_SAMPLES, acceleration_samples);
	if(current_acceleration <= ASCTODES_ACCELERATION_THRESHOLD)
		change_state(DESCENDING_PRE_MAIN);
}

void state_descending_pre_main() {
	noTone(BUZZER_PIN);
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEFAULT_SERVO_POSITION);

	int button_state = read_button_once();
	if(button_state == TRUE)
		change_state(DESCENDING_POST_MAIN);
	
	float current_altitude = average_array(ALTITUDE_N_SAMPLES, altitude_samples);
	if(current_altitude <= DEPLOY_ALTITUDE_THRESHOLD)
		change_state(DESCENDING_POST_MAIN);
}

void state_descending_post_main() {
	noTone(BUZZER_PIN);
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEPLOY_SERVO_POSITION);

	int button_state = read_button_once();
	if(button_state == TRUE)
		change_state(GROUNDED);

	float current_acceleration = average_array(ACCELERATION_N_SAMPLES, acceleration_samples);
	if(abs(current_acceleration) <= GROUNDED_ACCELERATION)
		change_state(DESCENDING_PRE_MAIN);
}

void state_grounded() {
	noTone(BUZZER_PIN);
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEPLOY_SERVO_POSITION);

	int button_state = read_button_once();
	if(button_state == TRUE)
		change_state(POWER_OFF);
}