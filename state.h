#pragma once

#define POWER_OFF 0
#define IDLE 1
#define ASCENDING 2
#define DESCENDING_PRE_MAIN 3
#define DESCENDING_POST_MAIN 4
#define GROUNDED 5

void change_state(int new_state);
int get_current_state();
