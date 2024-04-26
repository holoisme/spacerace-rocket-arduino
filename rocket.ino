
#include "I2C.h"
#include "state.h"
#include "board.h"
#include "utils.h"
#include "config.h"
#include "sdapi.h"

float* altitude_samples;

void setup() {
	Serial.begin(9600);
	Serial.println("Initializing Arduino Nano...");
	open_file();
	setup_layout();
	change_state(POWER_OFF);

	altitude_samples = calloc(ALTITUDE_N_SAMPLES, sizeof(float));
	if(altitude_samples == NULL)
		Serial.println("Not enough memory !");
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
	delay(DT);
}

void update_sensor_samples() {
	populate_array(ALTITUDE_N_SAMPLES, altitude_samples, read_altitude);
}

float get_current_altitude() {
	return average_array(ALTITUDE_N_SAMPLES, altitude_samples);
}

float get_current_velocity() {
	return compute_deltas(ALTITUDE_N_SAMPLES, altitude_samples) / DT_s;
}

void record_change_state(int new_state) {
	change_state(new_state);
	write_change_state(get_timestamp(), new_state);
}

void state_power_off() {
	digitalWrite(LED_BUILTIN, LOW);
	set_servo(DEFAULT_SERVO_POSITION);
	noTone(BUZZER_PIN);

	Serial.print("Altitude: ");
	Serial.println(get_current_altitude());
	Serial.print("Velocity: ");
	Serial.println(get_current_velocity());

	int button_state = read_button_once();
	if(button_state == TRUE)
		record_change_state(IDLE);
}

void state_idle() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEFAULT_SERVO_POSITION);
	tick_no_delay(IDLE_TICK_INTERVAL, IDLE_TICK_FREQUENCY);

	write_to_file(get_timestamp(), get_current_altitude(), get_current_velocity(), read_temperature(), read_pressure());

	int button_state = read_button_once();
	if(button_state == TRUE)
		record_change_state(ASCENDING);

	if(get_current_velocity() >= IDLE_VELOCITY_THRESHOLD && get_current_altitude() >= IDLE_ALTITUDE_THRESHOLD)
		record_change_state(ASCENDING);
}

void state_ascending() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEFAULT_SERVO_POSITION);
	tick_continuously_no_delay(1000, 250, 350);

	write_to_file(get_timestamp(), get_current_altitude(), get_current_velocity(), read_temperature(), read_pressure());

	int button_state = read_button_once();
	if(button_state == TRUE)
		record_change_state(DESCENDING_PRE_MAIN);

	if(get_current_velocity() <= ASCTODES_VELOCITY_THRESHOLD)
		record_change_state(DESCENDING_PRE_MAIN);
}

void state_descending_pre_main() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEFAULT_SERVO_POSITION);
	tick_continuously_no_delay(1000, 150, 250);

	write_to_file(get_timestamp(), get_current_altitude(), get_current_velocity(), read_temperature(), read_pressure());

	int button_state = read_button_once();
	if(button_state == TRUE)
		record_change_state(DESCENDING_POST_MAIN);
	
	if(get_current_altitude() <= DEPLOY_ALTITUDE_THRESHOLD)
		record_change_state(DESCENDING_POST_MAIN);
}

void state_descending_post_main() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEPLOY_SERVO_POSITION);
	tick_continuously_no_delay(1000, 100, 250);

	write_to_file(get_timestamp(), get_current_altitude(), get_current_velocity(), read_temperature(), read_pressure());

	int button_state = read_button_once();
	if(button_state == TRUE)
		record_change_state(GROUNDED);

	if(abs(get_current_velocity()) <= GROUNDED_VELOCITY)
		record_change_state(GROUNDED);
}

void state_grounded() {
	digitalWrite(LED_BUILTIN, HIGH);
	set_servo(DEPLOY_SERVO_POSITION);
	noTone(BUZZER_PIN);

	write_to_file(get_timestamp(), get_current_altitude(), get_current_velocity(), read_temperature(), read_pressure());

	int button_state = read_button_once();
	if(button_state == TRUE)
		record_change_state(POWER_OFF);

	close_file();
}