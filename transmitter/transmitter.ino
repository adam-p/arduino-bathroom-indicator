#include <VirtualWire.h>

uint8_t CLOSED_MSG_CHAR = '0';
uint8_t OPEN_MSG_CHAR = '1';

int ledPin = 13;
int txPin = 12;
int doorPin = 8;
int photocellPin = A0;


void setup()
{
  Serial.begin(9600);
  
  // We'll show the door state on the LED
  pinMode(ledPin, OUTPUT);
  
  pinMode(doorPin, INPUT);
  digitalWrite(doorPin, HIGH);  // turn on pullup resistors
  
  vw_set_ptt_inverted(true);  // Required for RF Link Module
  vw_setup(2000);  // Bits per sec
  vw_set_tx_pin(txPin);
}


// When the switch is closed (i.e., the door is closed), the pin will read LOW
const int DOOR_OPEN = HIGH;
const int DOOR_CLOSED = LOW;

void loop()
{
  int doorState = digitalRead(doorPin);
  
  int photocellReading = analogRead(photocellPin);
  
  // We're going to leave in this serial debugging output because we might need to 
  // adjust our light threshold for the particular installation in the particular room.
  Serial.println(photocellReading);
  
  // Testing has shown that a photocell reading (with a 1K resistor) below
  // about 100 is a good indicator of the bathroom light being off.
  photocellReading = (photocellReading < 100) ? LOW : HIGH;

  // We consider the bathroom occupied if and only if the door is closed and the light is on.
  uint8_t sendVal = OPEN_MSG_CHAR;
  if (doorState == DOOR_CLOSED && photocellReading == HIGH) {
    sendVal = CLOSED_MSG_CHAR;
  }
  
  vw_send(&sendVal, 1);
  vw_wait_tx();  // Wait for message to finish

  digitalWrite(ledPin, sendVal == OPEN_MSG_CHAR);
  delay(100);
}

