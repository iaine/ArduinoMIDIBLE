### Arduino IoT sonification

This code uses the Arduino BLE-MIDI code to scan for BLE devices. 

At the moment, on discovery it sends a simple MIDI note to a connected MIDI device. The volume is affected by a heuristic based on the received signal strength mapped within the MIDI volume range. 

There are todos such as different models.  

## Requirements
Arduino-BLE v 1.3.1
BLE-MIDI  v 2.2.0
MIDI v 5.0.2

## Tested
This code was tested on a Uno Wifi Rev 2 and a Nano 33 BLE. The former is more stable. 

The latter disconnects randomly which is something to be investigated. 
