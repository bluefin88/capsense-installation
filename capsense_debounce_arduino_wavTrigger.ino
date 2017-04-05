#include <CapacitiveSensor.h>
#include <AltSoftSerial.h>
#include <wavTrigger.h>

wavTrigger wTrig;                    // Our WAV Trigger object

const int led = 13;
const int delayTime = 50;


// CAPSENSE
const int resolution = 100;          // Settings
const int sensitivity = 600;         // Settings
const int debounce = 200;            // Settings

// Construct Capsense objects and store in array
CapacitiveSensor cs[] = {
  CapacitiveSensor(23, 4),
  CapacitiveSensor(23, 5),
  CapacitiveSensor(23, 6),
  CapacitiveSensor(23, 7),
  CapacitiveSensor(23, 8),
  CapacitiveSensor(23, 9)
};

// Delare Time and Sensor Arrays
const int NUMBER_OF_SENSORS = 6;
long timeArr[NUMBER_OF_SENSORS];
long sensorArr[NUMBER_OF_SENSORS];


void setup()
{ 
   // Initialize Arduino LED and Serial
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  // Initialize Capsense Array Objects
  for (int i = 0; i++; i < NUMBER_OF_SENSORS - 1) {
    timeArr[i] = 0;                                 // Set all sensor timers to 0...
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);        // Calibrate Capsense sensors...
  }

  // Initialize WAV Trigger
  wTrig.start();
  delay(1000);
}
void loop(){
  
  // Read sensors and store it in sensorObj Array, required because sensorArr type is long, different from capsense type
  for(int i=0; i<NUMBER_OF_SENSORS; i++){
    sensorArr[i] = cs[i].capacitiveSensor(resolution);
    //for Calibration CHANGED TO 1 
    Serial.println(sensorArr[3]);
  }

  // Conditional to check if any of the values in the sensorArr exceed threshold, if true, sensor is active
  // Sensor activation placed in a separate function in anticipation of other potential behavour when sensor is active, i.e. LED Lights
  for(int i=0; i<NUMBER_OF_SENSORS; i++){
    
    if (sensorArr[i]>sensitivity){
      activateSensor(i);
    }
  }
  delay(delayTime);
}


void activateSensor(int x){
  if (millis() - timeArr[x] > debounce) {
    Serial.println(millis() - timeArr[x]);
    Serial.print("Sensor = ");
    Serial.println(x);
    Serial.println(sensorArr[x]);
    wTrig.trackStop(x+4); // Stop track that is playing already? 
    wTrig.trackPlayPoly(x+4);   // Play relevant track CHANGED to +4 To play 004,005,006
  }
  timeArr[x] = millis();
}

