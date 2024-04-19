#include "state.h"

int current_state;

void change_state(int new_state) {
	current_state = new_state;
	
	Serial.print("Switching to ");
	switch(get_current_state()) {
		case POWER_OFF: Serial.println("powered off."); break;
		case IDLE: Serial.println("idle."); break;
		case ASCENDING: Serial.println("ascending."); break;
		case DESCENDING_PRE_MAIN: Serial.println("descending 1."); break;
		case DESCENDING_POST_MAIN: Serial.println("descending 2."); break;
		case GROUNDED: Serial.println("grounded."); break;
	}
}

int get_current_state() { return current_state; }
