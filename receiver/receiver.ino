#include <VirtualWire.h>

uint8_t CLOSED_MSG_CHAR = '0';
uint8_t OPEN_MSG_CHAR = '1';

int ledPin = 13;
int rxPin = 12;

void setup()
{
  // We'll show the door state on the LED
  pinMode(ledPin, OUTPUT);
  
  vw_set_ptt_inverted(true);  // Required for RF Link Module
  vw_set_rx_pin(rxPin);
  vw_setup(2000);  // Bits per sec
  vw_rx_start();  // Start the receiver
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) { // Non-blocking
    // Message with a good checksum received.
    
    if (buflen == 1 && buf[0] == OPEN_MSG_CHAR) {
      digitalWrite(ledPin, HIGH);
    }  
    else if (buflen == 1 && buf[0] == CLOSED_MSG_CHAR) {
      digitalWrite(ledPin, LOW);
    }
  }
}

