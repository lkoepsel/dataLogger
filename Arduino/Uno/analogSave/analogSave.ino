// analogSave:  Reads an analog pin and saves the values to EEPROM.
// If a value has not changed in the EEPROM, it is not overwritten
// Excessive writes to EEPROM reduce the EEPROM life span unnecessarily
// Values written to EEPROM will remain when power is removed from uC

// Add the funtions which control the EEPROM storage
#include <EEPROM.h>

// global variables used in program
int address = 0;              // beginning address at which to store data
int sensorPin = A0;           // set the input pin to be read
unsigned int sensorValue = 0; // variable to store the sensor value
unsigned int wait_ms = 1000;   // amount of time in ms to wait
unsigned int now;             // time stamp for data
int memorySize = EEPROM.length()/(sizeof(sensorValue) + sizeof(now));

// function to use to "stop" the uC by using an infinite loop
void stop()
{
    while(1) {};
}

// setup function for initializing uC, req'd by Arduino
// initialize the serial port and print a header for the data
void setup() 
{
    Serial.begin(115200);
    Serial.println("Address\tTime\tData");
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() 
{
    // read the value from the sensor and get the elapsed time:
    sensorValue = analogRead(sensorPin);
    now = millis();

    // print address, store time at address then get next available address
    Serial.print(address);
    EEPROM.put(address, now);
    address += sizeof(now);

    // store sensor value and set the next available address
    EEPROM.put(address, sensorValue);
    address += sizeof(sensorValue);

    // print time and sensor value
    Serial.print("\t");
    Serial.print(now);
    Serial.print("\t ");
    Serial.println(sensorValue);

    // check if the next address exceeds EEPROM capacity, if so, stop
    if (address >= memorySize) 
    {
        Serial.println("Out of memory");
        stop();
    }

    // if not, wait then continue to read and store values
    delay(wait_ms);
}
