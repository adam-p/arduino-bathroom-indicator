# Loo free?

An arduino-based wireless bathroom occupancy indicator.

...Because I'm super lazy and hate going all the way downstairs to find out someone's in the bog already. And then walking back up and wondering when they might be out.

This is my first Arduino project. Any feedback -- of any kind -- would be greatly appreciated.


## Libraries

Both transmitter and receiver use the [VirtualWire](http://www.airspayce.com/mikem/arduino/) library to make the (flaky, unstable) communiation easier.


## Receiver

![Receiver breadboard schematic](https://raw.github.com/adam-p/arduino-bathroom-indicator/master/receiver/receiver_bb.png)

### Parts

* [RF link receiver](http://www.creatroninc.com/index.php/prowr-010533.html)
  - Note that the dangling blue wire in the schematic is a wire used as an antenna. You should probably strip the plastic casing off most of it.


## Transmitter

![Transmitter breadboard schematic](https://raw.github.com/adam-p/arduino-bathroom-indicator/master/transmitter/transmitter_bb.png)

### Parts

* [RF link transmitter](http://www.creatroninc.com/index.php/wireless/radio-communication/prowr-010535.html)
  - The pins on mine aren't labeled, so the datasheet on that page was essential.
  - Note that the dangling blue wire in the schematic is a wire used as an antenna. You should probably strip the plastic casing off most of it.

* [Magnetic contact switch (door sensor)](http://www.adafruit.com/products/375)

* [Photo cell (CdS photoresistor)](http://www.adafruit.com/products/161), aka light sensor
  - Great photocell information [here](http://learn.adafruit.com/photocells/using-a-photocell).

* 1KΩ resistor
  - Probably a 10KΩ resistor would be better, but I don't have one. If you use one, you'll probably to change the threshold used for the light reading.