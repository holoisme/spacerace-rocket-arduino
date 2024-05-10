#include "sdapi.h"
#include "board.h"
#include "state.h"
#include <SD.h>

File file;

void open_file() {
	if (!SD.begin(SPI_CS_PIN)) {
		Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
		return;
	}
	Serial.println(F("SD CARD INITIALIZED."));

	SD.remove("data.txt");
	Serial.println(F("Creating data.txt file..."));
	file = SD.open("data.txt", FILE_WRITE);

	if (SD.exists("data.txt")) {
		Serial.println(F("data.txt exists on SD Card."));
	} else {
		Serial.println(F("data.txt doesn't exist on SD Card."));
	}
}

void write_change_state(unsigned long timestamp, int state) {
	if(!file)
		return;
	file.print(timestamp);
	file.print(":");
	switch(state) {
		case POWER_OFF: file.println("#POWERED_OFF"); break;
		case IDLE: file.println("#IDLE"); break;
		case ASCENDING: file.println("#ASCENDING"); break;
		case DESCENDING_PRE_MAIN: file.println("#DESCENDING_1"); break;
		case DESCENDING_POST_MAIN: file.println("#DESCENDING_2"); break;
		case GROUNDED: file.println("#GROUNDED"); break;
	}
}

void write_to_file(unsigned long timestamp, float altitude, float velocity, float temperature, float pressure) {
	if(!file) {
		Serial.println(F("SD Card: error on opening file data.txt"));
		return;
	}
	file.print(timestamp);
	file.print(":");
	file.print(altitude);
	file.print(",");
	file.print(velocity);
	file.print(",");
	file.print(temperature);
	file.print(",");
	file.print(pressure);
	file.print("\n");
}

void close_file() {
	if(file) {
		Serial.println("Closing file...");
		file.close();
	}
}