#include <VirtualWire.h>

uint8_t CLOSED_MSG_CHAR = '0';
uint8_t OPEN_MSG_CHAR = '1';

int ledPin = 13;
int txPin = 12;

void setup()
{
  // We'll show the door state on the LED
  pinMode(ledPin, OUTPUT);
  
  vw_set_ptt_inverted(true);  // Required for RF Link Module
  vw_setup(2000);  // Bits per sec
  vw_set_tx_pin(txPin);
}


const unsigned long sendDuration = 2000;
unsigned long flipTime = millis();  // TODO: Handle overflow
uint8_t sendVal = OPEN_MSG_CHAR;
uint8_t ledOut = HIGH;

void loop()
{
  if ((millis() - flipTime) > sendDuration) {
    flipTime = millis();
    sendVal = (sendVal == OPEN_MSG_CHAR) ? CLOSED_MSG_CHAR : OPEN_MSG_CHAR;
    ledOut = (sendVal == OPEN_MSG_CHAR) ? HIGH : LOW;
  }
  
  vw_send(&sendVal, 1);
  vw_wait_tx();  // Wait for message to finish

  digitalWrite(ledPin, ledOut);
  delay(100);
}

