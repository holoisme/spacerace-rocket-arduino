#include "state.h"

int current_state;

void change_state(int new_state) { current_state = new_state; }
int get_current_state() { return current_state; }
