# Melopero_RV-3028_Arduino_Library

This library provides an easy access to the RV3028 rtc functions.

## Usage

First you need to import the library and create the device object:

```C++
#include "Melopero_RV3028.h"

Melopero_RV3028 rtc;
```

Then you have to initialize the device inside the setup function:

```C++
...

void setup(){
    ...
    rtc.initDevice();
}

```

The initDevice function configures the Wire library needed to communicate with the sensor and performs all the required reset/initialization functions.

### Setting the time

You can set the time with the setTime function:

```C++
rtc.setTime(year, month, weekday, date, hour, minute, second);
// Note: the time is always set in 24h format (even if you are using the 12 hour format)
// Note: month value ranges from 1 (Jan) to 12 (Dec)
// Note: date value ranges from 1 to 31

```

**Note:** Thanks to the battery of the sensor you don't have to set the time each time you power up the sensor.

### Getting the time

To read the time you can use the following functions:

```C++
uint8_t second = sensor.getSecond();
uint8_t minute = sensor.getMinute();
uint8_t hour = sensor.getHour();
// if you are using the 12h format
bool pm = sensor.isPM();

uint8_t weekday = sensor.getWeekday();
uint8_t date = sensor.getDate();
uint8_t month = sensor.getMonth();
uint16_t year = sensor.getYear();

uint32_t unixtime = sensor.getUnixTime();
```

### Using the 12h format

If you want there is the option to use the 12h format for the time output:

```C++
sensor.set24HourMode();
sensor.set12HourMode();
bool is12hMode = is12HourMode();
bool pm = isPM();
```

### Alarm, Timers and Periodic Timers

### Using the EEPROM