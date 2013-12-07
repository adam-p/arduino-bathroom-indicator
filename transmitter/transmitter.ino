#include <VirtualWire.h>

uint8_t CLOSED_MSG_CHAR = '0';
uint8_t OPEN_MSG_CHAR = '1';

int ledPin = 13;
int txPin = 12;
int doorPin = 8;


void setup()
{
  // We'll show the door state on the LED
  pinMode(ledPin, OUTPUT);
  
  pinMode(doorPin, INPUT);
  digitalWrite(doorPin, HIGH);  // turn on pullup resistors
  
  vw_set_ptt_inverted(true);  // Required for RF Link Module
  vw_setup(2000);  // Bits per sec
  vw_set_tx_pin(txPin);
}


void loop()
{
  // When the switch is closed (i.e., the door is closed, the pin will read LOW
  int doorState = digitalRead(doorPin);

  uint8_t sendVal = (doorState == LOW) ? CLOSED_MSG_CHAR : OPEN_MSG_CHAR;
  
  vw_send(&sendVal, 1);
  vw_wait_tx();  // Wait for message to finish

  digitalWrite(ledPin, doorState);
  delay(100);
}

