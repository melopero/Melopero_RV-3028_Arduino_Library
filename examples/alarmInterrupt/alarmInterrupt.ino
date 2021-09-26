#include "Melopero_RV3028.h"

Melopero_RV3028 rtc;

// select a valid int pin for your arduino. You can check which pin can be used
// as interrupt listeners here: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/?setlang=en
byte intPin = 0;
bool interruptOccurred = false;

void interruptCallback(){
    interruptOccurred = true;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // First initialize and create the rtc device
  Wire.begin();
  rtc.initI2C();
 
  // Set the device to use the 24hour format (default) instead of the 12 hour format
  rtc.set24HourMode();

  // Set the date and time:
  rtc.setTime(2020, 9, 3, 30, 15, 20, 0);
  // year, month, weekday, date, hour, minute, second
  // Note: time is always set in 24h format
  // Note: month value ranges from 1 (Jan) to 12 (Dec)
  // Note: date value ranges from 1 to 31

  // print datetime to make sure everything works
  printTime();

  // set the interrupt to trigger every day at 1 minute from now
  // since we set the hour to 15:20 we don't have to check if the 
  // minute value exceeds 59...
  rtc.setDateModeForAlarm(false);
  rtc.enableAlarm(/* weekdayOrDate not important */ 0, /* hour */ rtc.getHour(), /* minute */ rtc.getMinute() + 1,
            /* dateAlarm */ false, /* hourAlarm */ true, /* minuteAlarm */ true, /* generateInterrupt */ true);

  // setup the pin to listen for the interrupt
  pinMode(intPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intPin), interruptCallback, CHANGE);
}

void loop() {

    if (interruptOccurred) {
        interruptOccurred = false;
        // BEEEP BEEEEP the alarm went off
        Serial.println("BEEEEP BEEEEP");
        printTime();
    }
  
}

void printTime(){
  Serial.print(rtc.getHour());
  Serial.print(":");
  Serial.print(rtc.getMinute());
  Serial.print(":");
  Serial.print(rtc.getSecond());
  Serial.print("   ");
  Serial.print(rtc.getDate());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.println(rtc.getYear());
}
