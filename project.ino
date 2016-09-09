/* CREATED BY ROSS KEDDY */

#include <NewPing.h>
#include <NewTone.h>
 
#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance to ping for (in centimeters).
#define ALARM 9  // Alarm 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
boolean triggered = false; 

float sinVal;
int toneVal;

void setup(){;
    triggered = false;
    pinMode(ALARM, OUTPUT);
    delay(500);
    Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop(){
    if(triggered == true){
      alarm();
    }
    else{
      delay(50);// Wait 50ms between pings (about 20 pings/sec).
      unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds.
      unsigned int distance = uS / US_ROUNDTRIP_CM;
      Serial.println(distance); //debug | prints distance to monitor
      if(distance < 5){ // Triggers alarm at said distance
         triggered = true;
      }
   }
   
//===================================
   char inChar = (char)Serial.read();
    if (inChar == 'y') {
      noNewTone(9); //stops so it doesn't drive you crazy
      triggered = false;
    }
}

void alarm(){
     for (int x=0; x<180; x++) {
        sinVal = (sin(x*(3.1412/180))); // convert degrees to radians then obtain sin value
        toneVal = 2000+(int(sinVal*1000));// generate a frequency from the sin value
        NewTone(ALARM, toneVal);
      }
}
