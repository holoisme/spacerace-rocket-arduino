#include "utils.h"

int last_start_tick = 0;
int last_finished_tick = 0;
int currently_ticking = 0;

void tick_no_delay(int interval, int frequency) {
	int current_time = millis();
	if(current_time - last_finished_tick >= interval) {
		if(currently_ticking == 0) {
			last_start_tick = current_time;
			currently_ticking = 1;
		}

		int advancement = current_time - last_start_tick;

		if(advancement >= 0 && advancement <= 50) {
			tone(BUZZER_PIN, frequency, 50);
		} else if(advancement <= 70) {
			noTone(BUZZER_PIN);
		} else if(advancement <= 120) {
			tone(BUZZER_PIN, frequency, 50);
		} else {
			noTone(BUZZER_PIN);
			currently_ticking = 0;
			last_finished_tick = millis();
		}
	}
}

int con_last_change = 0;
int con_phase = 0;

void tick_continuously_no_delay(int interval, int frequencyA, int frequencyB) {
	int current_time = millis();
	if(current_time - con_last_change >= interval) {
    con_last_change = current_time;
		con_phase = 1 - con_phase;

		if(con_phase == 0)
			tone(BUZZER_PIN, frequencyA, interval);
		else tone(BUZZER_PIN, frequencyB, interval);
	}
}

int N_ALTITUDE_SAMPLES = 0;

void populate_array(int size, float* array, float (*func)()) {
	for(int i = 1; i < size; i++)
		array[i - 1] = array[i];
	array[size - 1] = func();

	N_ALTITUDE_SAMPLES++;
	if(N_ALTITUDE_SAMPLES >= size)
		N_ALTITUDE_SAMPLES = size;
}

float average_array(int size, float* array) {
	float sum = 0.0f;
	for(int i = size - N_ALTITUDE_SAMPLES; i < size; i++)
		sum += array[i];
	return sum / (float)N_ALTITUDE_SAMPLES;
}

float compute_deltas(int size, float *array) {
	float sum = 0.0f;
	for(int i = size - N_ALTITUDE_SAMPLES + 1; i < size; i++)
		sum += array[i] - array[i - 1];
	return sum / (float)(N_ALTITUDE_SAMPLES - 1);
}