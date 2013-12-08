/*
 * Copyright Adam Pritchard 2013
 * MIT License : http://adampritchard.mit-license.org/
 */

// This library eases our wireless communication
#include <VirtualWire.h>

// Since we're only trying to represent two states -- occupied and unoccupied --
// we'll send just a single character between transmitter and receiver.
// Note that these values must be identical between transmitter and receiver
// (and I haven't figured out how to have a shared header file defining the values).
uint8_t OCCUPIED_MSG_CHAR = '0';
uint8_t UNOCCUPIED_MSG_CHAR = '1';

// We'll use the LED built into the Leonardo board
int ledPin = 13;

// Data pin for the RF wireless receiver
int rxPin = 12;


void setup()
{
  // We'll show the occupied state on the LED
  pinMode(ledPin, OUTPUT);
  
  /*
   * Setup the wireless receiver
   */
  // Required for RF Link Module (but I don't really understand it)
  vw_set_ptt_inverted(true);
  // Set to receive
  vw_set_rx_pin(rxPin);
  // Bits per second. Must match the value in the transmitter code. See note there.
  vw_setup(1000); 
  // Start the receiver
  vw_rx_start();
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Attempt to read from the wireless receiver
  if (vw_get_message(buf, &buflen)) { // Non-blocking
    // Message with a good checksum received.
    
    if (buflen == 1 && buf[0] == UNOCCUPIED_MSG_CHAR) {
      // We got our "bathroom unoccupied" message, so turn the LED on
      digitalWrite(ledPin, HIGH);
    }  
    else if (buflen == 1 && buf[0] == OCCUPIED_MSG_CHAR) {
      // We got our "bathroom occupied" message, so turn the LED off
      digitalWrite(ledPin, LOW);
    }
  }
}

