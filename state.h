#pragma once

#define POWER_OFF 0
#define IDLE 1
#define ASCENDING 2
#define DESCENDING 3
#define GROUNDED 4

void change_state(int new_state);
int get_current_state();
