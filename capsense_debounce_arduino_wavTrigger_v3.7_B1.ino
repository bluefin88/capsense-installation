/**************************************************
  COPPER TUBE SOUND TRIGGER WITH CAPSENSE v3.7
  
  GROUP 1

  Arduino sketch for Analogfolk Hong Kong's entrance installation.
  A series of suspended copper tubing can be triggered to create sound when touched.
  Can support up to 11 sensors before the MEGA processors starts to become too slow.
  As installation requires 33 sensors, each circuit is duplicated 3 times with 11 sensors each.
  This is the code Group 1 of 3.

  Components:
  * Arduino MEGA - for sensor processing
  * Sparkfun WAV Trigger - for polyphonic sound

  Roster:
  * Group 1: Sensors 1 - 11
  * Group 2: Sensors 12 - 22
  * Group 3: Sensors 23 - 33
  
  Created 29 December 2017
  By Wallace Wong

**************************************************/

#include <CapacitiveSensor.h>
#include <AltSoftSerial.h>
#include <wavTrigger.h>

wavTrigger wTrig;                   // WAV Trigger object

const int RESOLUTION = 30;          // Number of samples to take per Capsense reading
const int DEBOUNCE = 200;           // Time before sensor can be triggered again
const long SENSITIVITY[] = {        // Threshold that current have to exceed to register as trigger
  250, // Sensor 1
  250, // Sensor 2
  250, // Sensor 3
  250, // Sensor 4
  250, // Sensor 5
  200, // Sensor 6
  200, // Sensor 7
  200, // Sensor 8
  200, // Sensor 9
  300, // Sensor 10
  300  // Sensor 11
};

// Construct Capsense objects and store in array
// Pin 6 has low SENSITIVITY on this Arduino MEGA and is avoided
CapacitiveSensor cs[] = {
  CapacitiveSensor(23, 2),  // Sensor 1
  CapacitiveSensor(23, 3),  // Sensor 2
  CapacitiveSensor(23, 4),  // Sensor 3
  CapacitiveSensor(23, 5),  // Sensor 4
  CapacitiveSensor(23, 7),  // Sensor 5
  CapacitiveSensor(23, 8),  // Sensor 6
  CapacitiveSensor(23, 9),  // Sensor 7
  CapacitiveSensor(23, 10), // Sensor 8
  CapacitiveSensor(23, 11), // Sensor 9
  CapacitiveSensor(23, 12), // Sensor 10
  CapacitiveSensor(23, 13)  // Sensor 11*/
};

// Delay Time and Sensor Arrays
const int NUMBER_OF_SENSORS = 11;
long timeArr[NUMBER_OF_SENSORS];


void setup() { 
  Serial.begin(9600); // Allows readings to show on laptop

  // Initialize Capsense Array Objects
  for (int i = 0; i++; i < NUMBER_OF_SENSORS) {
    timeArr[i] = 0;                                 // Set all sensor timers to 0
    //cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);        // Set time auto re-calibraion of sensors. 0xFFFFFFFF = OFF
  }
  
  wTrig.start();    // Initialize WAV Trigger
  delay(1000);
}


void loop(){
  for(int i = 0; i < NUMBER_OF_SENSORS; i++) {
    long reading = cs[i].capacitiveSensor(RESOLUTION);
    
    /* Debug*/
    long individual = cs[1].capacitiveSensor(RESOLUTION);
    Serial.println(individual);
    
    if (reading > SENSITIVITY[i]) {
      activateSensor(i);
      Serial.print(reading);
      Serial.print(" = Reading, sensor is ");
      Serial.print(i+1);
      Serial.println();
    }
    delay(10);
  }
}


/**
  Checks if trigger is greater than debounce, 
  if so trigger WAV Trigger to play track relevant to sensor
  
  @param x Sensor ID.
  
  WAV Trigger sound files start count using from 1.
  Hence trackPlayPoly = Sensor ID + 1
*/

void activateSensor(int x) {
  if (millis() - timeArr[x] > DEBOUNCE) {
    wTrig.trackPlayPoly(x+1);
  }
  timeArr[x] = millis();
}

