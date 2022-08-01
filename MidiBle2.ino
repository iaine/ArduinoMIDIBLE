#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ArduinoBLE.h>

BLEMIDI_CREATE_DEFAULT_INSTANCE()

bool isConnected = false;

// -----------------------------------------------------------------------------
// When BLE connected, a MIDI note is sent to the connected machines
// Runs a scan and then sends a simple note per device to a connected device
// -----------------------------------------------------------------------------
void setup()
{
  
  MIDI.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  BLEMIDI.setHandleConnected([]() {
    isConnected = true;
  });

  BLEMIDI.setHandleDisconnected([]() {
    isConnected = false;
    digitalWrite(LED_BUILTIN, HIGH);
  });

  MIDI.setHandleNoteOn([](byte channel, byte note, byte velocity) {
    digitalWrite(LED_BUILTIN, LOW);
  });
  MIDI.setHandleNoteOff([](byte channel, byte note, byte velocity) {
    digitalWrite(LED_BUILTIN, HIGH);
  });

  BLE.setEventHandler(BLEDiscovered, bleCentralDiscoverHandler);
  BLE.scan(true);
  
}

// -----------------------------------------------------------------------------
//  Loop only polls for the data. It does not read. 
// -----------------------------------------------------------------------------
void loop()
{

  BLE.poll();

}

void bleCentralDiscoverHandler(BLEDevice peripheral) {
  int velocity = calculateVolume(peripheral.rssi());
  MIDI.sendNoteOn(60, velocity, 1);
}

int calculateVolume (int rssi) {
  return (int) ceil(128 * fabs(rssi)/100);
}
