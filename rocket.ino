
#include "I2C.h"
#include "state.h"
#include "board.h"

void setup() {
  Serial.begin(9600);
  setup_layout();
  change_state(POWER_OFF);
}

void loop() {
  switch(get_current_state()) {
    case POWER_OFF: state_power_off(); break;
    case IDLE: state_idle(); break;
    case ASCENDING: state_ascending(); break;
    case DESCENDING: state_descending(); break;
    case GROUNDED: state_grounded(); break;
  }
  delay(1);
}

void state_power_off() {
  noTone(BUZZER_PIN);
  digitalWrite(LED_BUILTIN, LOW);

  int button_state = digitalRead(BUTTON_PIN);
  if(button_state == LOW) {
    change_state(IDLE);
  }
}

void state_idle() {
  digitalWrite(LED_BUILTIN, HIGH);  
}

void state_ascending() {

}

void state_descending() {

}

void state_grounded() {

}