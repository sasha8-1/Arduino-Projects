#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired


#define LedPinOff 10
#define LedPinOn 11
#define LightPin 9

#define ValueSensor 4000

// state of switch
bool stateSwitch = false;
bool stateSwitchLast = false;
bool stateLed = false;

void setup()
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);

   pinMode(LedPinOff, OUTPUT);
   pinMode(LedPinOn, OUTPUT);
   pinMode(LightPin, OUTPUT);

  // waiting initialization device
   delay(2000);

}



void loop()
{

long start = millis();
long total =  cs_4_2.capacitiveSensor(30);

stateSwitch = total > ValueSensor ? true : false;

if (stateSwitch && stateSwitchLast == false) {
  stateLed = !stateLed;
  stateSwitchLast = true;
} else {
  stateSwitchLast = stateSwitch;
}

digitalWrite(LedPinOff, stateLed);
digitalWrite(LightPin, !stateLed);
digitalWrite(LedPinOn, !stateLed);



Serial.print(total);
Serial.println();
delay(10);
}
