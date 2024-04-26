#pragma once

void open_file();
void write_change_state(unsigned long timestamp, int state);
void write_to_file(unsigned long timestamp, float altitude, float velocity, float temperature, float pressure);
void close_file();