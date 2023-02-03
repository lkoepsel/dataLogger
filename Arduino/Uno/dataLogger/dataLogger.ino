// dataLogger:  Waits 10s then reads analog pin and saves the values to EEPROM
// 10 second wait allows user to load new program onto Uno to read data
// Blinking LED will show status, fast blink indicates 10s wait
// Slow rate indicates writing data to EEPROM, 1 blink per write

// Add the funtions which control the EEPROM storage
#include <EEPROM.h>

// global variables used in program
unsigned int address = 0;     // beginning address at which to store data
unsigned int sensorPin = A0;  // set the input pin to be read
unsigned int sensorValue = 0; // variable to store the sensor value
unsigned int wait_ms = 1000;  // amount of time in ms to wait
unsigned int now;             // time stamp for data
unsigned int memorySize = EEPROM.length()/(sizeof(sensorValue) + sizeof(now));
unsigned int start_time = 10;  // n seconds before logging data
unsigned int start_blinks = 10;  // n/2 blinks per second, indicate startup
unsigned int capture_delay = 2;  // n seconds before logging data
unsigned int capture_blinks = 2;  // n/2 blinks per second, indicate capture

// captureData: read analog pin, display and store values
void captureData();

// blink: delay for n seconds, blinking n/2 times per second
void blink(unsigned int seconds, unsigned int times);

// "stop" the uC by using an empty infinite loop, use to exit void loop()
void stop();

// setup function for initializing uC, req'd by Arduino
// initialize serial port, print a header for the data, delay/blink n start_time
void setup() 
{
    Serial.begin(115200);

    // initialize digital pin LED_BUILTIN (pin 13) as an output
    pinMode(13, OUTPUT);

    // delay to allow user to upload a different program to Uno, if desired
    blink(start_time, start_blinks);
    Serial.println("Address\tTime\tData");
}

// infinite loop for executing code without stopping, req'd by Arduino
void loop() 
{
    captureData();
}

void captureData()
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
    blink(capture_delay, capture_blinks);
}

void blink(unsigned int seconds, unsigned int times)
{
    for (unsigned int i = 0; i < seconds; i++) 
    {
        for (unsigned int j = 0; j < times; j++) 
        {    
            digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000/times/2); // wait for a second, blinking 
            digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
            delay(1000/times/2); // wait for a second, blinking
        }
    }
}

void stop()
{
    while(1) {};
}
