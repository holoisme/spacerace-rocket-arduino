#pragma once

#define FALSE 0
#define TRUE 1

void tick_no_delay(int interval, int frequency);
void populate_array(int size, float* array, float (*func)());
float average_array(int size, float* array);