#include <CapacitiveSensor.h>
#include <AltSoftSerial.h>
#include <wavTrigger.h>

wavTrigger wTrig;                    // Our WAV Trigger object

// CAPSENSE
const int resolution = 30;          // Settings
const long sensitivity = 250;         // Settings
const int debounce = 200;            // Settings

// Construct Capsense objects and store in array
// Pin 6 has low sensitivity
CapacitiveSensor cs[] = {
  CapacitiveSensor(23, 2),
  CapacitiveSensor(23, 3),
  CapacitiveSensor(23, 4),
  CapacitiveSensor(23, 5), 
  CapacitiveSensor(23, 7),
  CapacitiveSensor(23, 8),
  CapacitiveSensor(23, 9),
  CapacitiveSensor(23, 10),
  CapacitiveSensor(23, 11),
  CapacitiveSensor(23, 12),
  CapacitiveSensor(23, 13),
  CapacitiveSensor(23, 24),
  CapacitiveSensor(23, 25)
};

// Delay Time and Sensor Arrays
const int NUMBER_OF_SENSORS = 13;
long timeArr[NUMBER_OF_SENSORS];


void setup()
{ 
   // Initialize Arduino LED and Serial
  Serial.begin(9600);
  //pinMode(led, OUTPUT);

  // Initialize Capsense Array Objects
  for (int i = 0; i++; i < NUMBER_OF_SENSORS) {
    timeArr[i] = 0;                                 // Set all sensor timers to 0...
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);        // Calibrate Capsense sensors...
  }

  // Initialize WAV Trigger
  wTrig.start();
  delay(1000);
}

void loop(){
  for(int i = 0; i < NUMBER_OF_SENSORS; i++){
    long reading = cs[i].capacitiveSensor(resolution);
    if (reading > sensitivity) {
      activateSensor(i);
    }
    delay(10);
  }
}

void activateSensor(int x){
  //Sends command to WAV trigger to play a track after checking debounce
  if (millis() - timeArr[x] > debounce) {
    wTrig.trackPlayPoly(x+1);
  }
  timeArr[x] = millis();
}
