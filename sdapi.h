#pragma once

void open_file();
void write_change_state(int state);
void write(float altitude, float velocity, float temperature, float pressure);
void close_file();