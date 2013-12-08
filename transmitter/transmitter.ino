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

// Data pin for the RF wireless transmitter
int txPin = 12;

// Digital pin connected to the door sensor switch
int doorPin = 8;

// Analog pin connected to the light sensor
int photocellPin = A0;


void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
  
  // We'll show the occupied state on the LED
  pinMode(ledPin, OUTPUT);
  
  // Set the pin used by the door closed sensor as a digital input
  pinMode(doorPin, INPUT);
  // Turn on pullup resistors, as is required by our sensor (and maybe all switches?)
  digitalWrite(doorPin, HIGH);
  
  /*
   * Setup the wireless transmitter
   */
  // Required for RF Link Module (but I don't really understand it)
  vw_set_ptt_inverted(true);  
  // Set to transmit.
  vw_set_tx_pin(txPin);
  // Bits per second. The VirtualWire documentation (http://www.airspayce.com/mikem/arduino/VirtualWire.pdf)
  // suggests that using a lower bps will result in a higher effective range. Since we're 
  // only sending a single byte we might as well maximize our distance. (Note that
  // hardware I'm using claims a maximum of 4800 baud.)
  vw_setup(1000);
}


// When the switch is closed (i.e., the door is closed), the pin will read LOW
const int DOOR_OPEN = HIGH;
const int DOOR_CLOSED = LOW;

void loop()
{
  // Is the door open or closed?
  int doorState = digitalRead(doorPin);
  
  // Read the light level.
  // See here for info about this: http://learn.adafruit.com/photocells/using-a-photocell
  int photocellReading = analogRead(photocellPin);
  
  // We're going to leave in this serial debugging output because we might need to 
  // adjust our light threshold for the actual installation in the actual room.
  Serial.println(photocellReading);
  
  // Testing has shown that a photocell reading (with a 1K resistor) below
  // about 100 is a good indicator of the bathroom light being off.
  photocellReading = (photocellReading < 100) ? LOW : HIGH;

  // We consider the bathroom occupied if and only if the door is closed and the light is on.
  // Sometimes people leave the light on but the door open. Sometimes people leave the door 
  // closed but the light off. But no one leaves (or should leave) the light on and the door 
  // closed unless they're occupying it.
  uint8_t sendVal = UNOCCUPIED_MSG_CHAR;
  if (doorState == DOOR_CLOSED && photocellReading == HIGH) {
    sendVal = OCCUPIED_MSG_CHAR;
  }
  
  // Send our state to the receiver.
  vw_send(&sendVal, 1);
  vw_wait_tx();  // Wait for message to finish

  // Set the state of our LED
  digitalWrite(ledPin, sendVal == UNOCCUPIED_MSG_CHAR);
  
  // This delay isn't really necessary. But there's not much of a reason to check the
  // bathroom state (and resend the state message) more than 10 times a second.
  delay(100);
}

