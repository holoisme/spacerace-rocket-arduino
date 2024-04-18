#pragma once

#define FALSE 0
#define TRUE 1

int last_start_tick = 0;
int last_finished_tick = 0;
int currently_ticking = 0;

void tick_no_delay(int interval) {
	int current_time = millis();
	if(current_time - last_finished_tick >= interval) {
		if(currently_ticking == 0) {
			last_start_tick = current_time;
			currently_ticking = 1;
		}

		int advancement = current_time - last_start_tick;

		if(advancement >= 0 && advancement <= 50) {
			tone(BUZZER_PIN, 262, 50);
		} else if(advancement <= 70) {
			noTone(BUZZER_PIN);
		} else if(advancement <= 120) {
			tone(BUZZER_PIN, 262, 50);
		} else {
			noTone(BUZZER_PIN);
			currently_ticking = 0;
			last_finished_tick = millis();
		}
	}
}